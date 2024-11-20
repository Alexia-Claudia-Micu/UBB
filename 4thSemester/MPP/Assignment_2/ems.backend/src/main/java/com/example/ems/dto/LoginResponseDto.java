package com.example.ems.dto;


import com.example.ems.entity.ApplicationUser;

public class LoginResponseDto {
    private ApplicationUser user;
    private String token;

    public LoginResponseDto() {
        super();
    }

    public LoginResponseDto(ApplicationUser user, String jwt) {
        super();
        this.user = user;
        this.token = jwt;
    }

    public ApplicationUser getUser() {
        return user;
    }

    public void setUser(ApplicationUser user) {
        this.user = user;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }
}
