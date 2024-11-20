package com.example.ems.mapper;

import com.example.ems.dto.SeasonDto;
import com.example.ems.entity.Season;

public class SeasonMapper {
    public static SeasonDto mapToSeasonDto(Season season){
        return new SeasonDto(
                season.getId(),
                season.getName(),
                season.getDescription(),
                season.getNrDays()
        );
    }

    public static Season mapToSeason(SeasonDto seasonDto){
        return new Season(
                seasonDto.getId(),
                seasonDto.getName(),
                seasonDto.getDescription(),
                seasonDto.getNrDays()
        );
    }
}
