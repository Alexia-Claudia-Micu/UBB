package com.example.ems;

import com.example.ems.ResourceNotFoundException;
import com.example.ems.dto.HolidayDto;
import com.example.ems.entity.Holiday;
import com.example.ems.mapper.HolidayMapper;
import com.example.ems.repository.HolidayRepository;
import com.example.ems.service.impl.HolidayService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

class HolidayServiceTests {

    @Mock
    private HolidayRepository holidayRepository;

    @InjectMocks
    private HolidayService holidayService;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    void testDeleteAllHolidays() {
        holidayService.deleteAllHolidays();
        verify(holidayRepository, times(1)).deleteAll();
    }

    @Test
    void testCreateHoliday() {
        HolidayDto holidayDto = new HolidayDto();
        holidayDto.setName("New Year");
        Holiday holiday = new Holiday();
        holiday.setName("New Year");

        when(holidayRepository.save(any(Holiday.class))).thenReturn(holiday);

        HolidayDto savedHolidayDto = holidayService.createHoliday(holidayDto);

        assertEquals("New Year", savedHolidayDto.getName());
    }

    @Test
    void testGetHolidayById() {
        Holiday holiday = new Holiday();
        holiday.setId(1L);
        holiday.setName("Christmas");

        when(holidayRepository.findById(1L)).thenReturn(Optional.of(holiday));

        HolidayDto holidayDto = holidayService.getHolidayById(1L);

        assertEquals("Christmas", holidayDto.getName());
    }

    @Test
    void testGetHolidayById_NotFound() {
        when(holidayRepository.findById(1L)).thenReturn(Optional.empty());

        assertThrows(ResourceNotFoundException.class, () -> holidayService.getHolidayById(1L));
    }

    @Test
    void testGetHolidayBySeasonId() {
        Holiday holiday1 = new Holiday();
        holiday1.setId(1L);
        holiday1.setSeasonId(1L);
        holiday1.setName("Thanksgiving");

        Holiday holiday2 = new Holiday();
        holiday2.setId(2L);
        holiday2.setSeasonId(1L);
        holiday2.setName("Christmas");

        when(holidayRepository.findAll()).thenReturn(Arrays.asList(holiday1, holiday2));

        List<HolidayDto> holidayDtos = holidayService.getHolidayBySeasonId(1L);

        assertEquals(2, holidayDtos.size());
    }

    @Test
    void testGetAllHolidays() {
        Holiday holiday1 = new Holiday();
        holiday1.setId(1L);
        holiday1.setName("Thanksgiving");

        Holiday holiday2 = new Holiday();
        holiday2.setId(2L);
        holiday2.setName("Christmas");

        when(holidayRepository.findAll()).thenReturn(Arrays.asList(holiday1, holiday2));

        List<HolidayDto> holidayDtos = holidayService.getAllHolidays();

        assertEquals(2, holidayDtos.size());
    }

    @Test
    void testUpdateHoliday() {
        HolidayDto updatedHolidayDto = new HolidayDto();
        updatedHolidayDto.setSeasonId(1L);
        updatedHolidayDto.setName("Updated Name");
        updatedHolidayDto.setDay(25);
        updatedHolidayDto.setDescription("Updated Description");

        Holiday holiday = new Holiday();
        holiday.setId(1L);
        holiday.setSeasonId(1L);
        holiday.setName("Original Name");
        holiday.setDay(24);
        holiday.setDescription("Original Description");

        when(holidayRepository.findById(1L)).thenReturn(Optional.of(holiday));
        when(holidayRepository.save(any(Holiday.class))).thenReturn(holiday);

        HolidayDto updatedDto = holidayService.updateHoliday(1L, updatedHolidayDto);

        assertEquals("Updated Name", updatedDto.getName());
        assertEquals(25, updatedDto.getDay());
        assertEquals("Updated Description", updatedDto.getDescription());
    }

    @Test
    void testDeleteHoliday() {
        Holiday holiday = new Holiday();
        holiday.setId(1L);

        when(holidayRepository.findById(1L)).thenReturn(Optional.of(holiday));

        holidayService.deleteHoliday(1L);

        verify(holidayRepository, times(1)).deleteById(1L);
    }

    @Test
    void testDeleteHoliday_NotFound() {
        when(holidayRepository.findById(1L)).thenReturn(Optional.empty());

        assertThrows(ResourceNotFoundException.class, () -> holidayService.deleteHoliday(1L));
    }
}
