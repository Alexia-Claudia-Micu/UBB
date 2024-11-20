package com.example.ems;

import com.example.ems.controller.HolidayController;
import com.example.ems.dto.HolidayDto;
import com.example.ems.service.IHolidayService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.ArgumentMatchers.*;
import static org.mockito.Mockito.*;

class HolidayControllerTests {

    @Mock
    private IHolidayService holidayService;

    @InjectMocks
    private HolidayController holidayController;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    void testDeleteAllHolidays() {
        ResponseEntity<String> responseEntity = holidayController.deleteAllHolidays();
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        verify(holidayService, times(1)).deleteAllHolidays();
    }

    @Test
    void testCreateHoliday() {
        HolidayDto holidayDto = new HolidayDto();
        holidayDto.setName("New Year");

        when(holidayService.createHoliday(any(HolidayDto.class))).thenReturn(holidayDto);

        ResponseEntity<HolidayDto> responseEntity = holidayController.createHoliday(holidayDto);
        assertEquals(HttpStatus.CREATED, responseEntity.getStatusCode());
        assertEquals("New Year", responseEntity.getBody().getName());
    }

    @Test
    void testGetHolidayById() {
        HolidayDto holidayDto = new HolidayDto();
        holidayDto.setId(1L);
        holidayDto.setName("Christmas");

        when(holidayService.getHolidayById(1L)).thenReturn(holidayDto);

        ResponseEntity<HolidayDto> responseEntity = holidayController.getHolidayById(1L);
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        assertEquals("Christmas", responseEntity.getBody().getName());
    }

    @Test
    void testGetAllSeasons() {
        List<HolidayDto> holidayDtos = new ArrayList<>();
        HolidayDto holiday1 = new HolidayDto();
        holiday1.setName("New Year");
        holidayDtos.add(holiday1);

        when(holidayService.getAllHolidays()).thenReturn(holidayDtos);

        ResponseEntity<List<HolidayDto>> responseEntity = holidayController.getAllSeasons();
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        assertEquals(1, responseEntity.getBody().size());
        assertEquals("New Year", responseEntity.getBody().get(0).getName());
    }

    @Test
    void testUpdateHoliday() {
        HolidayDto updatedHolidayDto = new HolidayDto();
        updatedHolidayDto.setId(1L);
        updatedHolidayDto.setName("Updated Christmas");

        when(holidayService.updateHoliday(eq(1L), any(HolidayDto.class))).thenReturn(updatedHolidayDto);

        ResponseEntity<HolidayDto> responseEntity = holidayController.updateHoliday(1L, updatedHolidayDto);
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        assertEquals("Updated Christmas", responseEntity.getBody().getName());
    }

    @Test
    void testDeleteHoliday() {
        ResponseEntity<String> responseEntity = holidayController.deleteHoliday(1L);
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        verify(holidayService, times(1)).deleteHoliday(1L);
    }
}
