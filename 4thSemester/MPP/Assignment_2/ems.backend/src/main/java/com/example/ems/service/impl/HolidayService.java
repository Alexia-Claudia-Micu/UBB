package com.example.ems.service.impl;

import com.example.ems.ResourceNotFoundException;
import com.example.ems.dto.HolidayDto;
import com.example.ems.entity.Holiday;
import com.example.ems.mapper.HolidayMapper;
import com.example.ems.repository.HolidayRepository;
import com.example.ems.service.IHolidayService;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Service
@AllArgsConstructor
public class HolidayService implements IHolidayService {
    private HolidayRepository holidayRepository;

    @Override
    public void deleteAllHolidays(){
        holidayRepository.deleteAll();
    }

    @Override
    public HolidayDto createHoliday(HolidayDto holidayDto) {
        Holiday holiday = HolidayMapper.mapToHoliday(holidayDto);
        Holiday savedHoliday = holidayRepository.save(holiday);

        return HolidayMapper.mapToHolidayDto(savedHoliday);
    }

    @Override
    public HolidayDto getHolidayById(Long holidayId) {
        Holiday holiday = holidayRepository.findById(holidayId)
                .orElseThrow(() -> new ResourceNotFoundException("Holiday does not exist with given id: " + holidayId));

        return HolidayMapper.mapToHolidayDto(holiday);
    }

    @Override
    public List<HolidayDto> getHolidayBySeasonId(Long seasonId) {
        return holidayRepository.findAll()
                .stream()
                .filter(holiday -> holiday.getSeasonId().equals(seasonId))
                .map(HolidayMapper::mapToHolidayDto)
                .collect(Collectors.toList());
    }
    @Override
    public List<HolidayDto> getAllHolidays() {
        List<Holiday> holidays = holidayRepository.findAll();
        return holidays.stream().map(HolidayMapper::mapToHolidayDto).collect(Collectors.toList());
    }

    @Override
    public HolidayDto updateHoliday(Long holidayId, HolidayDto updatedHoliday) {
        Holiday holiday = holidayRepository.findById(holidayId).orElseThrow(
                () -> new ResourceNotFoundException("Holiday does not exist with given id: " + holidayId)
        );

        holiday.setSeasonId(updatedHoliday.getSeasonId());
        holiday.setName(updatedHoliday.getName());
        holiday.setDay(updatedHoliday.getDay());
        holiday.setDescription(updatedHoliday.getDescription());

        Holiday updatedHolidayObj = holidayRepository.save(holiday);

        return HolidayMapper.mapToHolidayDto(updatedHolidayObj);
    }

    @Override
    public void deleteHoliday(Long holidayId) {
        Holiday holiday = holidayRepository.findById(holidayId)
                .orElseThrow(() -> new ResourceNotFoundException("Holiday does not exist with given id:" + holidayId));
        holidayRepository.deleteById(holidayId);
    }
}
