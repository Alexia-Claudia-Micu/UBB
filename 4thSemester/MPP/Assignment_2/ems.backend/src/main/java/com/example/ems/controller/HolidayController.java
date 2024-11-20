package com.example.ems.controller;

import com.example.ems.dto.HolidayDto;
import com.example.ems.dto.SeasonDto;
import com.example.ems.entity.Holiday;
import com.example.ems.service.IHolidayService;
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
@RequestMapping("/api/seasons/holiday")
public class HolidayController {

    private final IHolidayService holidayService;

    // build delete everything
    @DeleteMapping
    public ResponseEntity<String> deleteAllHolidays() {
        holidayService.deleteAllHolidays();
        return ResponseEntity.ok("All holidays deleted successfully!");
    }

    @Autowired
    public HolidayController(IHolidayService receivedService) {
        this.holidayService = receivedService;
    }

    // Build add holiday rest api
    @PostMapping
    public ResponseEntity<HolidayDto> createHoliday(@RequestBody HolidayDto holidayDto) {
        HolidayDto savedSeason = holidayService.createHoliday(holidayDto);
        return new ResponseEntity<>(savedSeason, HttpStatus.CREATED);
    }

    // Build get holiday rest api
    @GetMapping("{id}")
    public ResponseEntity<HolidayDto> getHolidayById(@PathVariable("id") Long holidayId) {
        HolidayDto holidayDto = holidayService.getHolidayById(holidayId);
        return ResponseEntity.ok(holidayDto);
    }



    // Build get all holiday rest api
    @GetMapping
    public ResponseEntity<List<HolidayDto>> getAllSeasons() {
        List<HolidayDto> holidayDtos = holidayService.getAllHolidays();
        return ResponseEntity.ok(holidayDtos);
    }


    // Build update holiday rest api
    @PutMapping("{id}")
    public ResponseEntity<HolidayDto> updateHoliday(@PathVariable("id") Long holidayId,
                                                  @RequestBody HolidayDto updatedHoliday) {
        HolidayDto holidayDto = holidayService.updateHoliday(holidayId, updatedHoliday);
        return ResponseEntity.ok(holidayDto);
    }


    // Build delete holiday rest api
    @DeleteMapping("{id}")
    public ResponseEntity<String> deleteHoliday(@PathVariable("id") Long holidayId) {
        holidayService.deleteHoliday(holidayId);
        return ResponseEntity.ok("Holiday deleted successfully.");
    }

}
