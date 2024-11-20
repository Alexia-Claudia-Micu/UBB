package com.example.ems.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class HolidayDto {
    private Long id;
    private Long seasonId;
    private String name;
    private int day;
    private String description;
}

