package com.mpp.Backend.model;

import jakarta.persistence.*;

import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "seasons")
public class Season {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "season_id")
    private int id;
    private String name;
    private int nrDays;
    private String description;

    @OneToMany(cascade = CascadeType.ALL)
    @JoinColumn(name = "fk_season_id", referencedColumnName = "season_id")
    private List<Holiday> holidays;

    @ManyToOne
    @JoinColumn(name = "fk_user_id", referencedColumnName = "user_id")
    private ApplicationUser applicationUser;

    public Season() {
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getNrDays() {
        return nrDays;
    }

    public void setNrDays(int nrDays) {
        this.nrDays = nrDays;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public List<Holiday> getHolidays() {
        return holidays;
    }

    public void setHolidays(List<Holiday> holidayList) {
        this.holidays = holidayList;
    }

    public ApplicationUser getApplicationUser() {
        return applicationUser;
    }

    public void setApplicationUser(ApplicationUser applicationUser) {
        this.applicationUser = applicationUser;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Season season) {
            boolean holidaysAreTheSame = true;
            if (season.holidays == null) season.holidays = new ArrayList<>();
            if (season.holidays.size() != holidays.size()) {
                holidaysAreTheSame = false;
            } else {
                for (int i = 0; i < season.holidays.size(); i++) {
                    if (season.holidays.get(i).getId() != season.holidays.get(i).getId()) {
                        holidaysAreTheSame = false;
                        break;
                    }
                }
            }

            return id == season.getId() && name.equals(season.getName()) && nrDays == season.getNrDays() && description.equals(season.getDescription()) && holidaysAreTheSame;
        }
        return false;
    }

    @Override
    public String toString() {
        return "Bird{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", description=" + description +
                ", days='" + nrDays + '\'' +
                '}';
    }
}
