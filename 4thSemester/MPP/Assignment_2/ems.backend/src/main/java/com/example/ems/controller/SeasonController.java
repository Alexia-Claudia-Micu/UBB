package com.example.ems.controller;
import com.example.ems.dto.SeasonDto;
import com.example.ems.service.IService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@CrossOrigin("*")
@RestController
@RequestMapping("/api/seasons")
public class SeasonController {
    private final IService service;
    private final SimpMessagingTemplate messagingTemplate;

    @Autowired
    public SeasonController(IService receivedService, SimpMessagingTemplate messagingTemplate) {
        this.service = receivedService;
        this.messagingTemplate = messagingTemplate;
    }

    // Build add season rest api
    @PostMapping
    public ResponseEntity<SeasonDto> createSeason(@RequestBody SeasonDto seasonDto) {
        SeasonDto savedSeason = service.createSeason(seasonDto);
        return new ResponseEntity<>(savedSeason, HttpStatus.CREATED);
    }

    // Build get season rest api
    @GetMapping("{id}")
    public ResponseEntity<SeasonDto> getSeasonById(@PathVariable("id") Long seasonId) {
        SeasonDto seasonDto = service.getSeasonById(seasonId);
        return ResponseEntity.ok(seasonDto);
    }



    // Build get all season rest api
    @GetMapping
    public ResponseEntity<List<SeasonDto>> getAllSeasons() {
        List<SeasonDto> seasons = service.getAllSeasons();
        return ResponseEntity.ok(seasons);
    }


    // Build update season rest api
    @PutMapping("{id}")
    public ResponseEntity<SeasonDto> updateSeason(@PathVariable("id") Long seasonId,
                                               @RequestBody SeasonDto updatedSeason) {
        SeasonDto seasonDto = service.updateSeason(seasonId, updatedSeason);
        return ResponseEntity.ok(seasonDto);
    }


    // Build delete season rest api
    @DeleteMapping("{id}")
    public ResponseEntity<String> deleteSeason(@PathVariable("id") Long seasonId) {
        service.deleteSeason(seasonId);
        return ResponseEntity.ok("Season deleted successfully.");
    }


    // WebSocket endpoint
    @MessageMapping("/websocket")
    public void handleWebSocketMessage(String message) {
        // Process WebSocket message here
        // You can also send messages back to the client using messagingTemplate
        messagingTemplate.convertAndSend("/topic/greetings", "Hello, client!");

    }
}