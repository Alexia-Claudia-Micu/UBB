package com.mpp.Backend.service;

import com.mpp.Backend.model.Holiday;
import com.mpp.Backend.model.Season;

import java.util.List;

public interface IService {
    boolean saveSeason(Season season);

    List<Season> getAllSeasons();

    Season getSeasonById(int id);

    boolean deleteSeason(int id);

    boolean updateSeason(int id, Season updatedSeason);

    List<Holiday> getHolidaysBySeasonId(int seasonId);

    Holiday getHolidayById(int seasonId, int holidayId);

    boolean addHoliday(int seasonId, Holiday holiday);

    boolean deleteHoliday(int seasonId, int holidayId);

    boolean updateHoliday(int seasonId, int holidayId, Holiday updatedHoliday);

    boolean otherUser(String username, int seasonId);

    List<Season> getAllSeasonsByUser(String username);

    Season getSeasonByIdByUser(String username, int seasonId);

    boolean updateSeasonByUser(String username, int seasonId, Season season);

    boolean deleteSeasonByUser(String username, int id);

    List<Holiday> getHolidaysBySeasonIdByUser(String username, int seasonId);

    Holiday getHolidayByIdByUser(String username, int seasonId, int holidayId);

    boolean addHolidayByUser(String username, int seasonId, Holiday holiday);

    boolean updateHolidayByUser(String username, int seasonId, int holidayId, Holiday holiday);

    boolean deleteHolidayByUser(String username, int seasonId, int holidayId);
}
