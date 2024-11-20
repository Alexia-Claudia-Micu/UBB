package com.example.ems.controller;


import com.example.ems.dto.LoginDto;
import com.example.ems.dto.LoginResponseDto;
import com.example.ems.dto.RegistrationDto;
import com.example.ems.entity.ApplicationUser;
import com.example.ems.service.impl.AuthenticationService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/auth")
public class AuthenticationController {

    @Autowired
    AuthenticationService authenticationService;

    @PostMapping("/register")
    public ApplicationUser registerUser(@RequestBody RegistrationDto body){
        return authenticationService.registerUser(body.getUsername(), body.getPassword(), body.getEmail());
    }

    @PostMapping("/login")
    public LoginResponseDto loginUser(@RequestBody LoginDto body){
        return authenticationService.loginUser(body.getUsername(), body.getPassword());
    }

    @PostMapping("/logout")
    public ResponseEntity<Void> logout(@RequestHeader("Authorization") String token) {
        if (token.startsWith("Bearer ")) {
            token = token.substring(7);
        }
        authenticationService.logoutUser(token);
        return ResponseEntity.ok().build();
    }
}
