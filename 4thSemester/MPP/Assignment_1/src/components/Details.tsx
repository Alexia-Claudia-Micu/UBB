// Details.js

import React from "react";
import { useParams } from "react-router-dom";
import Seasons from "./Seasons";

const Details = () => {
  const { name } = useParams();
  const season = Seasons.find(
    (s) => s.Name.toLowerCase() === name.toLowerCase()
  );

  return (
    <div>
      <h1>Details for {season && season.Name}</h1>
      {season && (
        <div>
          <p>Days: {season.Days}</p>
          <p>ID: {season.id}</p>
        </div>
      )}
    </div>
  );
};

export default Details;
