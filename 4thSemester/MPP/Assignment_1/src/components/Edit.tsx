import React, { useState, useEffect } from "react";
import { Button, Form } from "react-bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";
import Seasons from "./Seasons";
import { v4 as uuid } from "uuid";
import { Link, useNavigate } from "react-router-dom";

function Edit() {
  const [name, setName] = useState("");
  const [days, setDays] = useState(-1);
  const [id, setId] = useState("");

  let history = useNavigate();

  var index = Seasons.map(function (e) {
    return e.id;
  }).indexOf(id);

  const handleSubmit = (e: React.MouseEvent<HTMLButtonElement, MouseEvent>) => {
    e.preventDefault();
    let a = Seasons[index];
    a.Name = name;
    a.Days = days;

    history("/");
  };

  useEffect(() => {
    setName(localStorage.getItem("Name"));
    setDays(localStorage.getItem("Days"));
    setId(localStorage.getItem("Id"));
  }, []);

  return (
    <div>
      <Form className="d-grid gap-2" style={{ margin: "15rem" }}>
        <Form.Group className="mb-3" controlId="formName">
          <Form.Control
            type="text"
            placeholder="Enter Name"
            value={name}
            required
            onChange={(e) => setName(e.target.value)}
          ></Form.Control>
        </Form.Group>
        <Form.Group className="mb-3" controlId="formDays">
          <Form.Control
            type="text"
            placeholder="Enter Days"
            value={days}
            required
            onChange={(e) => setDays(parseInt(e.target.value))}
          ></Form.Control>
        </Form.Group>
        <Button onClick={(e) => handleSubmit(e)} type="submit">
          Update
        </Button>
      </Form>
    </div>
  );
}

export default Edit;
