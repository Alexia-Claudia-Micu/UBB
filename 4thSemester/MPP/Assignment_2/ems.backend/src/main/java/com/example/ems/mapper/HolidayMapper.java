package com.example.ems.mapper;

import com.example.ems.dto.HolidayDto;
import com.example.ems.dto.SeasonDto;
import com.example.ems.entity.Holiday;
import com.example.ems.entity.Season;

public class HolidayMapper {
    public static HolidayDto mapToHolidayDto(Holiday holiday){
        return new HolidayDto(
                holiday.getId(),
                holiday.getSeasonId(),
                holiday.getName(),
                holiday.getDay(),
                holiday.getDescription()
        );
    }

    public static Holiday mapToHoliday(HolidayDto holidayDto){
        return new Holiday(
                holidayDto.getId(),
                holidayDto.getSeasonId(),
                holidayDto.getName(),
                holidayDto.getDay(),
                holidayDto.getDescription()
        );
    }
}
