
function sortTable(columnIndex) {
  var table, rows, switching, i, x, y, shouldSwitch, dir, switchcount = 0;
  table = document.getElementById("sortable-table");
  switching = true;
  dir = "asc"; // Set the sorting direction to ascending by default

  // Remove arrows from all th elements
  var ths = table.getElementsByTagName("th");
  for (var i = 0; i < ths.length; i++) {
    ths[i].setAttribute("data-sort", "none");
    ths[i].classList.remove("asc", "desc");
  }

  while (switching) {
    switching = false;
    rows = table.rows;
    for (i = 1; i < (rows.length - 1); i++) {
      shouldSwitch = false;
      x = rows[i].getElementsByTagName("td")[columnIndex];
      y = rows[i + 1].getElementsByTagName("td")[columnIndex];
      if (dir == "asc") {
        if (parseInt(x.innerHTML) > parseInt(y.innerHTML)) {
          shouldSwitch = true;
          break;
        }
      } else if (dir == "desc") {
        if (parseInt(x.innerHTML) < parseInt(y.innerHTML)) {
          shouldSwitch = true;
          break;
        }
      }
    }
    if (shouldSwitch) {
      rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
      switching = true;
      switchcount++;
    } else {
      if (switchcount == 0 && dir == "asc") {
        dir = "desc";
        switching = true;
      }
    }
  }

  var clickedTh = ths[columnIndex];
  clickedTh.setAttribute("data-sort", dir);
  clickedTh.classList.add(dir === "asc" ? "asc" : "desc");
}


var initialRowOrder = []; 

  window.onload = function() {
    var table = document.getElementById("sortable-table");
    var tbody = table.querySelector("tbody");
    var rows = tbody.getElementsByTagName("tr");

    for (var i = 0; i < rows.length; i++) {
      initialRowOrder.push(rows[i]);
    }
  };

  function restoreTable() {
    var table = document.getElementById("sortable-table");
    var ths = table.getElementsByTagName("th");

    for (var i = 0; i < ths.length; i++) {
      ths[i].setAttribute("data-sort", "none");
      ths[i].classList.remove("asc", "desc");
    }

    var tbody = table.querySelector("tbody");
    tbody.innerHTML = ""; 

    for (var i = 0; i < initialRowOrder.length; i++) {
      tbody.appendChild(initialRowOrder[i]);
    }
  }