package com.example.ems.service;

import com.example.ems.dto.HolidayDto;
import com.example.ems.dto.SeasonDto;
import com.example.ems.entity.Season;

import java.util.List;

public interface IService {
    SeasonDto createSeason(SeasonDto seasonDto);
    SeasonDto getSeasonById(Long seasonId);
    List<SeasonDto> getAllSeasons();
    SeasonDto updateSeason(Long seasonId, SeasonDto updatedSeason);
    void deleteSeason(Long seasonId);
}
