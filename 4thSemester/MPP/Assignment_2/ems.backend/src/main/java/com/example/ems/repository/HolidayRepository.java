package com.example.ems.repository;

import com.example.ems.entity.Holiday;
import com.example.ems.entity.Season;
import org.springframework.data.jpa.repository.JpaRepository;

public interface HolidayRepository extends JpaRepository<Holiday, Long> {

}