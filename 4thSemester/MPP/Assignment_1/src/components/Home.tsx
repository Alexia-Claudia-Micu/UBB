import React, { Fragment, useState } from "react";
import "bootstrap/dist/css/bootstrap.min.css";
import Seasons from "./Seasons";
import { Button, Table } from "react-bootstrap";
import { Link, useNavigate } from "react-router-dom";
import Chart from "react-google-charts";

export const options = {
  title: "Seasons",
};

export const data = [
  ["Season", "Days per Year"],
  ...Seasons.map((season) => [season.Name, season.Days]),
];

function Home() {
  const [sortByDays, setSortByDays] = useState(false);
  const [seasons, setSeasons] = useState(Seasons);
  const [currentPage, setCurrentPage] = useState(1);
  const itemsPerPage = 4;
  const totalPages = Math.ceil(seasons.length / itemsPerPage);
  const indexOfLastItem = currentPage * itemsPerPage;
  const indexOfFirstItem = indexOfLastItem - itemsPerPage;
  const currentSeasons = seasons.slice(indexOfFirstItem, indexOfLastItem);
  let history = useNavigate();

  const handleDetails = (name: string) => {
    let path = "/details/" + name;
    window.open(path, "_blank");
  };

  const handleEdit = (id: string, name: string, days: number) => {
    localStorage.setItem("Name", name);
    localStorage.setItem("Days", days.toString());
    localStorage.setItem("Id", id);
  };

  const handleDelete = (id: string) => {
    const updatedSeasons = seasons.filter((season) => season.id !== id);
    setSeasons(updatedSeasons);
    history("/");
  };

  const handleSort = () => {
    const sortedSeasons = [...seasons];
    sortedSeasons.sort((a, b) => {
      if (sortByDays) {
        return a.Days - b.Days;
      } else {
        return b.Days - a.Days;
      }
    });
    setSeasons(sortedSeasons);
    setSortByDays(!sortByDays);
  };

  const paginate = (pageNumber: React.SetStateAction<number>) =>
    setCurrentPage(pageNumber);

  return (
    <Fragment>
      <Chart
        chartType="PieChart"
        data={data}
        options={options}
        width={"100%"}
        height={"400px"}
      />
      <div style={{ margin: "10rem" }}>
        <Table striped bordered hover size="sm">
          <thead>
            <tr>
              <th>Name</th>
              <th>
                Days{" "}
                <Button variant="link" onClick={handleSort}>
                  {sortByDays ? "↑" : "↓"}
                </Button>
              </th>
              <th>Actions</th>
            </tr>
          </thead>
          <tbody>
            {currentSeasons.length > 0 ? (
              currentSeasons.map((item) => (
                <tr key={item.id}>
                  <td>{item.Name}</td>
                  <td>{item.Days}</td>
                  <td>
                    <Link to={"/edit"}>
                      <Button
                        onClick={() =>
                          handleEdit(item.id, item.Name, item.Days)
                        }
                      >
                        Update
                      </Button>
                    </Link>
                    &nbsp;
                    <Button onClick={() => handleDelete(item.id)}>
                      Delete
                    </Button>
                    &nbsp;
                    <Button onClick={() => handleDetails(item.Name)}>
                      Details
                    </Button>
                  </td>
                </tr>
              ))
            ) : (
              <tr>
                <td>No data available</td>
              </tr>
            )}
          </tbody>
        </Table>
        <div className="pagination">
          {Array.from({ length: totalPages }, (_, i) => (
            <Button key={i} onClick={() => paginate(i + 1)}>
              {i + 1}
            </Button>
          ))}
        </div>
        <br />
        <Link className="d-grid gap-2" to="/create">
          <Button size="lg">Create</Button>
        </Link>
      </div>
    </Fragment>
  );
}

export default Home;
