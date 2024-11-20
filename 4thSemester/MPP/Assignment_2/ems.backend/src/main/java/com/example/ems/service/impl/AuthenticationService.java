package com.example.ems.service.impl;

import com.example.ems.dto.LoginResponseDto;
import com.example.ems.entity.ApplicationUser;
import com.example.ems.entity.Role;
import com.example.ems.repository.IRoleRepository;
import com.example.ems.repository.IUserRepository;
import com.example.ems.service.impl.TokenService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.HashSet;
import java.util.Set;

@Service
@Transactional
public class AuthenticationService {

    @Autowired
    private IUserRepository userRepository;

    @Autowired
    private IRoleRepository roleRepository;

    @Autowired
    private PasswordEncoder passwordEncoder;

    @Autowired
    private AuthenticationManager authenticationManager;

    @Autowired
    private TokenService tokenService;

    public ApplicationUser registerUser(String username, String password, String email) {
        String encodedPassword = passwordEncoder.encode(password);
        Role userRole = roleRepository.findByAuthority("USER").get();

        Set<Role> authorities = new HashSet<>();
        authorities.add(userRole);

        return userRepository.save(new ApplicationUser(0, username, encodedPassword, email, authorities));
    }

    public LoginResponseDto loginUser(String username, String password) {
        try {
            Authentication auth = authenticationManager.authenticate(
                    new UsernamePasswordAuthenticationToken(username, password)
            );

            String token = tokenService.generateJwt(auth);
            return new LoginResponseDto(userRepository.findByUsername(username).get(), token);

        } catch (AuthenticationException e) {
            return new LoginResponseDto(null, "");
        }
    }

    public void logoutUser(String token) {
        tokenService.blacklistToken(token);
    }
}
