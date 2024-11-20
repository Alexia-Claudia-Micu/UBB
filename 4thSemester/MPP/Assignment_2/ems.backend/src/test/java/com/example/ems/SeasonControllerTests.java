package com.example.ems;

import com.example.ems.controller.SeasonController;
import com.example.ems.dto.SeasonDto;
import com.example.ems.service.IService;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.simp.SimpMessagingTemplate;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.ArgumentMatchers.*;
import static org.mockito.Mockito.*;

class SeasonControllerTests {

    @Mock
    private IService service;

    @Mock
    private SimpMessagingTemplate messagingTemplate;

    @InjectMocks
    private SeasonController seasonController;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    void testCreateSeason() {
        SeasonDto seasonDto = new SeasonDto();
        seasonDto.setName("Spring");

        when(service.createSeason(any(SeasonDto.class))).thenReturn(seasonDto);

        ResponseEntity<SeasonDto> responseEntity = seasonController.createSeason(seasonDto);
        assertEquals(HttpStatus.CREATED, responseEntity.getStatusCode());
        assertEquals("Spring", responseEntity.getBody().getName());
    }

    @Test
    void testGetSeasonById() {
        SeasonDto seasonDto = new SeasonDto();
        seasonDto.setId(1L);
        seasonDto.setName("Summer");

        when(service.getSeasonById(1L)).thenReturn(seasonDto);

        ResponseEntity<SeasonDto> responseEntity = seasonController.getSeasonById(1L);
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        assertEquals("Summer", responseEntity.getBody().getName());
    }

    @Test
    void testGetAllSeasons() {
        List<SeasonDto> seasonDtos = new ArrayList<>();
        SeasonDto season1 = new SeasonDto();
        season1.setName("Spring");
        seasonDtos.add(season1);

        when(service.getAllSeasons()).thenReturn(seasonDtos);

        ResponseEntity<List<SeasonDto>> responseEntity = seasonController.getAllSeasons();
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        assertEquals(1, responseEntity.getBody().size());
        assertEquals("Spring", responseEntity.getBody().get(0).getName());
    }

    @Test
    void testUpdateSeason() {
        SeasonDto updatedSeasonDto = new SeasonDto();
        updatedSeasonDto.setId(1L);
        updatedSeasonDto.setName("Updated Summer");

        when(service.updateSeason(eq(1L), any(SeasonDto.class))).thenReturn(updatedSeasonDto);

        ResponseEntity<SeasonDto> responseEntity = seasonController.updateSeason(1L, updatedSeasonDto);
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        assertEquals("Updated Summer", responseEntity.getBody().getName());
    }

    @Test
    void testDeleteSeason() {
        ResponseEntity<String> responseEntity = seasonController.deleteSeason(1L);
        assertEquals(HttpStatus.OK, responseEntity.getStatusCode());
        verify(service, times(1)).deleteSeason(1L);
    }

    @Test
    void testHandleWebSocketMessage() {
        // Test WebSocket message handling
        seasonController.handleWebSocketMessage("test message");
        // Verify that messagingTemplate was called
        verify(messagingTemplate, times(1)).convertAndSend(eq("/topic/greetings"), eq("Hello, client!"));
    }
}
