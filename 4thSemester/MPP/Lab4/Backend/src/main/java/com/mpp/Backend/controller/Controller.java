package com.mpp.Backend.controller;

import com.mpp.Backend.model.ApplicationUser;
import com.mpp.Backend.model.Season;
import com.mpp.Backend.model.Holiday;
import com.mpp.Backend.service.SeasonService;
import com.mpp.Backend.service.IService;
import com.mpp.Backend.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.web.bind.annotation.*;

import java.security.Principal;
import java.util.List;

@RestController
@RequestMapping("/season")
public class Controller {

    @Autowired
    private IService seasonService;

    @Autowired
    private UserService userService;

    @PostMapping("/add")
    public String addSeason(@RequestBody Season season, Principal principal) {
        ApplicationUser applicationUser = (ApplicationUser) userService.loadUserByUsername(principal.getName());
        season.setApplicationUser(applicationUser);
        if(seasonService.saveSeason(season)) {
            return "New season is added!";
        } else {
            return "Season could not be added!";
        }
    }

    @GetMapping("/getAll")
    public List<Season> getAllSeason(Principal principal) {
        return seasonService.getAllSeasonsByUser(principal.getName());
    }

    @GetMapping("/get/{id}")
    public Season getSeasonById(@PathVariable int id, Principal principal) {
        return seasonService.getSeasonByIdByUser(principal.getName(), id);
    }

    @PutMapping("/update/{id}")
    public String updateSeason(@PathVariable int id, @RequestBody Season season, Principal principal) {
        if(seasonService.updateSeasonByUser(principal.getName(), id, season)) {
            return "Season is updated!";
        }
        return "Season could not be updated!";
    }

    @DeleteMapping("/delete/{id}")
    public String deleteSeason(@PathVariable int id, Principal principal) {
        if(seasonService.deleteSeasonByUser(principal.getName(), id)) {
            return "Season is deleted!";
        }
        return "Season could not be deleted!";
    }

    @GetMapping("/{seasonId}/holiday/getAll")
    public List<Holiday> getHolidaysBySeasonId(@PathVariable int seasonId, Principal principal) {
        return seasonService.getHolidaysBySeasonIdByUser(principal.getName(), seasonId);
    }

    @GetMapping("/{seasonId}/holiday/get/{holidayId}")
    public Holiday getHolidayById(@PathVariable int seasonId, @PathVariable int holidayId, Principal principal) {
        return seasonService.getHolidayByIdByUser(principal.getName(), seasonId, holidayId);
    }

    @PostMapping("/{seasonId}/holiday/add")
    public String addHoliday(@PathVariable int seasonId, @RequestBody Holiday holiday, Principal principal) {
        if (seasonService.addHolidayByUser(principal.getName(), seasonId, holiday)) {
            return "Holiday is added!";
        }
        return "Holiday could not be added!";
    }

    @PutMapping("/{seasonId}/holiday/update/{holidayId}")
    public String updateHoliday(@PathVariable int seasonId, @PathVariable int holidayId, @RequestBody Holiday holiday, Principal principal) {
        if (seasonService.updateHolidayByUser(principal.getName(), seasonId, holidayId, holiday)) {
            return "Holiday is updated!";
        }
        return "Holiday could not be updated!";
    }

    @DeleteMapping("/{seasonId}/holiday/delete/{holidayId}")
    public String deleteHoliday(@PathVariable int seasonId, @PathVariable int holidayId, Principal principal) {
        if(seasonService.deleteHolidayByUser(principal.getName(), seasonId, holidayId)) {
            return "Holiday is deleted!";
        }
        return "Holiday could not be deleted!";
    }
}
