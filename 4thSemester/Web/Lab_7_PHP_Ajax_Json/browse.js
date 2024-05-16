var filter = "None";
var opt = "None";
function jsonParse(text) {
    let json;
    try {
        json = JSON.parse(text);
    } catch (e) {
        return false;
    }
    return json;
}

function get_filtered_by_color(){
    var ajax = new XMLHttpRequest();

    ajax.onreadystatechange = function(){
        if(this.readyState === 4 && this.status === 200){
            let table = document.getElementsByTagName("table")[0];
            let oldTableBody = document.getElementsByTagName("tbody")[0];

            let newTableBody = document.createElement('tbody');
            
            let json = jsonParse(this.responseText);
            for(let i = 0; i < json.length; i++){
                let car = json[i];
                let row = newTableBody.insertRow();
                Object.keys(car).forEach(function (k){
                    let text;
                    let cell = row.insertCell();
                    text = car[k];
                    cell.appendChild(document.createTextNode(text));
                })
            }
            table.appendChild(newTableBody);
            oldTableBody.parentNode.removeChild(oldTableBody);

        }
    }

    ajax.open('POST', 'getAllCarsByColor.php', true);
    let color = document.getElementsByTagName("select")[1].value;
    let json = JSON.stringify({'color': color});
    ajax.send(json);

    setPrevious("Color", color);

}


function get_filtered_by_model(){
    var ajax = new XMLHttpRequest();

    ajax.onreadystatechange = function(){
        if(this.readyState === 4 && this.status === 200){
            let table = document.getElementsByTagName("table")[0];
            let oldTableBody = document.getElementsByTagName("tbody")[0];

            let newTableBody = document.createElement('tbody');
            
            let json = jsonParse(this.responseText);
            for(let i = 0; i < json.length; i++){
                let cat = json[i];
                let row = newTableBody.insertRow();
                Object.keys(cat).forEach(function (k){
                    let text;
                    let cell = row.insertCell();
                    text = cat[k];
                    cell.appendChild(document.createTextNode(text));
                })
            }
            table.appendChild(newTableBody);
            oldTableBody.parentNode.removeChild(oldTableBody);
        }
    }

    ajax.open('POST', 'getAllCarsByModel.php', true);
    let model = document.getElementsByTagName("select")[0].value;
    let json = JSON.stringify({'model': model});
    ajax.send(json);

    setPrevious("Model", model);

}

function setPrevious(filt, option){
    document.getElementById("previous-filter").innerHTML = "Previously used: " + filter + " filter: " + opt;
    filter=filt;
    opt = option;

}
