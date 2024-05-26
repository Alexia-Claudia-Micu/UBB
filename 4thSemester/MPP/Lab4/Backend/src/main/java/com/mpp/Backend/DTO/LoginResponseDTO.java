package com.mpp.Backend.DTO;

import com.mpp.Backend.model.ApplicationUser;

public class LoginResponseDTO {
    private ApplicationUser user;
    private String token;

    public LoginResponseDTO() {
        super();
    }

    public LoginResponseDTO(ApplicationUser user, String jwt) {
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
