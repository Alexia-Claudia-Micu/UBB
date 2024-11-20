package com.example.ems;

import com.example.ems.ResourceNotFoundException;
import com.example.ems.dto.SeasonDto;
import com.example.ems.entity.Season;
import com.example.ems.mapper.SeasonMapper;
import com.example.ems.repository.SeasonRepository;
import com.example.ems.service.impl.ServiceImpl;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.scheduling.annotation.Scheduled;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

class SeasonServiceTest {

    @Mock
    private SeasonRepository seasonRepository;

    @InjectMocks
    private ServiceImpl seasonService;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    void testAddNewSeason() {
        // This method doesn't return anything, so we can just verify that save method is called
        seasonService.addNewSeason();
        verify(seasonRepository, times(1)).save(any(Season.class));
    }

    @Test
    void testCreateSeason() {
        SeasonDto seasonDto = new SeasonDto();
        seasonDto.setName("Spring");
        seasonDto.setDescription("Warm season");
        seasonDto.setNrDays(30);

        Season season = new Season();
        season.setName("Spring");
        season.setDescription("Warm season");
        season.setNrDays(30);

        when(seasonRepository.save(any(Season.class))).thenReturn(season);

        SeasonDto savedSeasonDto = seasonService.createSeason(seasonDto);

        assertEquals("Spring", savedSeasonDto.getName());
        assertEquals("Warm season", savedSeasonDto.getDescription());
        assertEquals(30, savedSeasonDto.getNrDays());
    }

    @Test
    void testGetSeasonById() {
        Season season = new Season();
        season.setId(1L);
        season.setName("Summer");

        when(seasonRepository.findById(1L)).thenReturn(Optional.of(season));

        SeasonDto seasonDto = seasonService.getSeasonById(1L);

        assertEquals("Summer", seasonDto.getName());
    }

    @Test
    void testGetSeasonById_NotFound() {
        when(seasonRepository.findById(1L)).thenReturn(Optional.empty());

        assertThrows(ResourceNotFoundException.class, () -> seasonService.getSeasonById(1L));
    }

    @Test
    void testGetAllSeasons() {
        Season spring = new Season();
        spring.setId(1L);
        spring.setName("Spring");

        Season summer = new Season();
        summer.setId(2L);
        summer.setName("Summer");

        when(seasonRepository.findAll()).thenReturn(Arrays.asList(spring, summer));

        List<SeasonDto> seasonDtos = seasonService.getAllSeasons();

        assertEquals(2, seasonDtos.size());
    }

    @Test
    void testUpdateSeason() {
        SeasonDto updatedSeasonDto = new SeasonDto();
        updatedSeasonDto.setName("Updated Name");
        updatedSeasonDto.setDescription("Updated Description");
        updatedSeasonDto.setNrDays(60);

        Season season = new Season();
        season.setId(1L);
        season.setName("Original Name");
        season.setDescription("Original Description");
        season.setNrDays(30);

        when(seasonRepository.findById(1L)).thenReturn(Optional.of(season));
        when(seasonRepository.save(any(Season.class))).thenReturn(season);

        SeasonDto updatedDto = seasonService.updateSeason(1L, updatedSeasonDto);

        assertEquals("Updated Name", updatedDto.getName());
        assertEquals("Updated Description", updatedDto.getDescription());
        assertEquals(60, updatedDto.getNrDays());
    }

    @Test
    void testDeleteSeason() {
        Season season = new Season();
        season.setId(1L);

        when(seasonRepository.findById(1L)).thenReturn(Optional.of(season));

        seasonService.deleteSeason(1L);

        verify(seasonRepository, times(1)).deleteById(1L);
    }

    @Test
    void testDeleteSeason_NotFound() {
        when(seasonRepository.findById(1L)).thenReturn(Optional.empty());

        assertThrows(ResourceNotFoundException.class, () -> seasonService.deleteSeason(1L));
    }
}
