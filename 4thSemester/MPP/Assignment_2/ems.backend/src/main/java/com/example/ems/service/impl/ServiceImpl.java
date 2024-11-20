package com.example.ems.service.impl;

import com.example.ems.ResourceNotFoundException;
import com.example.ems.dto.HolidayDto;
import com.example.ems.dto.SeasonDto;
import com.example.ems.entity.Holiday;
import com.example.ems.entity.Season;
import com.example.ems.mapper.HolidayMapper;
import com.example.ems.mapper.SeasonMapper;
import com.example.ems.repository.HolidayRepository;
import com.example.ems.repository.SeasonRepository;
import com.example.ems.service.IService;
import lombok.AllArgsConstructor;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;


@Service
@AllArgsConstructor
public class ServiceImpl implements IService{

    private SeasonRepository seasonRepository;

    @Scheduled(fixedRate = 5000) // Add a new season every 60 seconds (adjust the interval as needed)
    public void addNewSeason() {
        Season newSeason = new Season(null, "a","d", 10);
        seasonRepository.save(newSeason);

    }

    @Override
    public SeasonDto createSeason(SeasonDto seasonDto) {
        Season season = SeasonMapper.mapToSeason(seasonDto);
        Season savedSeason = seasonRepository.save(season);

        return SeasonMapper.mapToSeasonDto(savedSeason);
    }

    @Override
    public SeasonDto getSeasonById(Long seasonId) {
        Season season = seasonRepository.findById(seasonId)
                .orElseThrow(() -> new ResourceNotFoundException("Season does not exist with given id : " + seasonId));

        return SeasonMapper.mapToSeasonDto(season);
    }

    @Override
    public List<SeasonDto> getAllSeasons() {
        List<Season> seasons = seasonRepository.findAll();
        return seasons.stream().map(SeasonMapper::mapToSeasonDto).collect(Collectors.toList());
    }

    @Override
    public SeasonDto updateSeason(Long seasonId, SeasonDto updatedSeason) {
        Season season = seasonRepository.findById(seasonId).orElseThrow(
                () -> new ResourceNotFoundException("Season does not exist with given id: " + seasonId)
        );

        season.setName(updatedSeason.getName());
        season.setDescription(updatedSeason.getDescription());
        season.setNrDays(updatedSeason.getNrDays());

        Season updatedSeasonObj = seasonRepository.save(season);

        return SeasonMapper.mapToSeasonDto(updatedSeasonObj);
    }

    @Override
    public void deleteSeason(Long seasonId) {
        Season season = seasonRepository.findById(seasonId)
                .orElseThrow(() -> new ResourceNotFoundException("Season does not exist with given id : " + seasonId));
        seasonRepository.deleteById(seasonId);
    }

}