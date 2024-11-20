import React, { useState } from "react";
import { Button, Form } from "react-bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";
import Seasons from "./Seasons";
import { v4 as uuid } from "uuid";
import { Link, useNavigate } from "react-router-dom";

function Add() {
  const [name, setName] = useState("");
  const [days, setDays] = useState(-1);

  let history = useNavigate();

  const handleSubmit = (e: React.MouseEvent<HTMLButtonElement, MouseEvent>) => {
    e.preventDefault();
    const ids = uuid();
    let uniqueId = ids.slice(0, 8);

    let a = name,
      b = days;

    Seasons.push({ id: uniqueId, Name: a, Days: b });
    history("/");
  };

  return (
    <div>
      <Form className="d-grid gap-2" style={{ margin: "15rem" }}>
        <Form.Group className="mb-3" controlId="formName">
          <Form.Control
            type="text"
            placeholder="Enter Name"
            required
            onChange={(e) => setName(e.target.value)}
          ></Form.Control>
        </Form.Group>
        <Form.Group className="mb-3" controlId="formDays">
          <Form.Control
            type="text"
            placeholder="Enter Days"
            required
            onChange={(e) => setDays(parseInt(e.target.value))}
          ></Form.Control>
        </Form.Group>
        <Button onClick={(e) => handleSubmit(e)} type="submit">
          Submit
        </Button>
      </Form>
    </div>
  );
}

export default Add;
