package com.mpp.Backend.model;

import jakarta.persistence.*;

@Entity
@Table(name = "holidays")
public class Holiday {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "holiday_id")
    private int id;
    private String name;
    private String description;
    private int nrDays;

    public Holiday() {
    }

    public int getId() {
        return id;
    }

//    public void setId(int id) {
//        this.id = id;
//    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public int getNrDays() {
        return nrDays;
    }

    public void setNrDays(int days) {
        this.nrDays = days;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Holiday e) {
            if (e.getId() == this.id && e.getName().equals(this.name)) {
                e.getDescription();
            }
            return false;
        }
        return false;
    }

    @Override
    public String toString() {
        return "Egg{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", description=" +description +
                ", days=" + nrDays +
                '}';
    }
}
