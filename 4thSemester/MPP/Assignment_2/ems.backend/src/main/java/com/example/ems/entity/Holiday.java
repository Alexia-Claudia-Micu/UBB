package com.example.ems.entity;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Entity
@Table(name = "holidays")
public class Holiday {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "seasonId")
    private Long seasonId;

    @Column(name = "name", nullable = false, unique = true)
    private String name;

    @Column(name = "day")
    private int day;

    @Column(name = "description")
    private String description;


}
