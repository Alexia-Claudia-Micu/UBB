package com.mpp.Backend.service;

import com.mpp.Backend.model.Season;
import com.mpp.Backend.model.Holiday;
import com.mpp.Backend.repository.ISeasonRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@Service
public class SeasonService implements IService{

    @Autowired
    private ISeasonRepository seasonRepository;

    @Override
    public boolean saveSeason(Season season) {
        Season seasonSaved = seasonRepository.save(season);
        return season.equals(seasonSaved);
    }

    @Override
    public List<Season> getAllSeasons() {
        return seasonRepository.findAll();
    }

    @Override
    public Season getSeasonById(int id) {
        return seasonRepository.findById(id).orElse(null);
    }

    @Override
    public boolean deleteSeason(int id) {
        try{
            seasonRepository.deleteById(id);
            return true;
        } catch (Exception e){
            return false;
        }
    }

    @Override
    public boolean updateSeason(int id, Season updatedSeason) {
        Season season = seasonRepository.getReferenceById(id);
        season.setName(updatedSeason.getName());
        season.setNrDays(updatedSeason.getNrDays());
        season.setDescription(updatedSeason.getDescription());
        season.setHolidays(updatedSeason.getHolidays());
        Season seasonSaved = seasonRepository.save(season);
        updatedSeason.setId(id);
        return seasonSaved.equals(updatedSeason);
    }

    @Override
    public List<Holiday> getHolidaysBySeasonId(int seasonId) {
        Season season = seasonRepository.findById(seasonId).orElse(null);
        if (season == null) return null;
        return season.getHolidays();
    }

    @Override
    public Holiday getHolidayById(int seasonId, int holidayId) {
        Season season = seasonRepository.findById(seasonId).orElse(null);
        if (season == null) return null;
        List<Holiday> holidays = season.getHolidays();
        if (holidays == null) return null;
        return holidays.stream().filter(e -> e.getId() == holidayId).findFirst().orElse(null);
    }

    @Override
    public boolean addHoliday(int seasonId, Holiday holiday) {
        Season season = seasonRepository.findById(seasonId).orElse(null);
        if (season == null) return false;
        season.getHolidays().add(holiday);
        seasonRepository.save(season);
        return true;
    }

    @Override
    public boolean deleteHoliday(int seasonId, int holidayId) {
        Season season = seasonRepository.findById(seasonId).orElse(null);
        if (season == null) return false;
        List<Holiday> holidays = new ArrayList<>();
        for (Holiday holiday : season.getHolidays()) {
            if (holiday.getId() != holidayId) {
                holidays.add(holiday);
            }
        }
        season.setHolidays(holidays);
        seasonRepository.save(season);
        return true;
    }

    @Override
    public boolean updateHoliday(int seasonId, int holidayId, Holiday updatedHoliday) {
        Season season = seasonRepository.findById(seasonId).orElse(null);
        if (season == null) return false;
        Holiday holiday = season.getHolidays().stream().filter(e -> e.getId() == holidayId).findFirst().orElse(null);
        if (holiday == null) return false;
        holiday.setName(updatedHoliday.getName());
        holiday.setDescription(updatedHoliday.getDescription());
        holiday.setNrDays(updatedHoliday.getNrDays());
        seasonRepository.save(season);
        return true;
    }

    @Override
    public boolean otherUser(String username, int seasonId) {
        return !getSeasonById(seasonId).getApplicationUser().getUsername().equals(username);
    }

    @Override
    public List<Season> getAllSeasonsByUser(String username) {
        return getAllSeasons().stream().filter(season -> Objects.equals(season.getApplicationUser().getUsername(), username)).toList();
    }

    @Override
    public Season getSeasonByIdByUser(String username, int seasonId) {
        Season season = getSeasonById(seasonId);
        if (season.getApplicationUser().getUsername().equals(username)) return season;
        return null;
    }

    @Override
    public boolean updateSeasonByUser(String username, int seasonId, Season updatedSeason) {
        if (otherUser(username, seasonId)) return false;
        return updateSeason(seasonId, updatedSeason);
    }

    @Override
    public boolean deleteSeasonByUser(String username, int id) {
        if (otherUser(username, id)) return false;
        return deleteSeason(id);
    }

    @Override
    public List<Holiday> getHolidaysBySeasonIdByUser(String username, int seasonId) {
        if (otherUser(username, seasonId)) return new ArrayList<>();
        return getHolidaysBySeasonId(seasonId);
    }

    @Override
    public Holiday getHolidayByIdByUser(String username, int seasonId, int holidayId) {
        if (otherUser(username, seasonId)) return null;
        return getHolidayById(seasonId, holidayId);
    }

    @Override
    public boolean addHolidayByUser(String username, int seasonId, Holiday holiday) {
        if (otherUser(username, seasonId)) return false;
        return addHoliday(seasonId, holiday);
    }

    @Override
    public boolean updateHolidayByUser(String username, int seasonId, int holidayId, Holiday holiday) {
        if (otherUser(username, seasonId)) return false;
        return updateHoliday(seasonId, holidayId, holiday);
    }

    @Override
    public boolean deleteHolidayByUser(String username, int seasonId, int holidayId) {
        if (otherUser(username, seasonId)) return false;
        return deleteHoliday(seasonId, holidayId);
    }


}
