package com.example.ems.service;

import com.example.ems.dto.HolidayDto;
import com.example.ems.dto.SeasonDto;

import java.util.List;

public interface IHolidayService {
    HolidayDto createHoliday(HolidayDto holidayDto);
    HolidayDto getHolidayById(Long holidayId);
    List<HolidayDto> getHolidayBySeasonId(Long seasonId);
    List<HolidayDto> getAllHolidays();
    HolidayDto updateHoliday(Long holidayId, HolidayDto updatedHoliday);
    void deleteHoliday(Long holidayId);

    void deleteAllHolidays();
}
