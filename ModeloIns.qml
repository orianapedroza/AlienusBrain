import QtQuick 2.0
//import "."
//Como obtenemos y separamos la informacion

ListModel {
    id: model

    Component.onCompleted:{
        readTextFile("content/data/DISCO_DURO.txt")
//        console.log("estoy aqui")
    }

    function readTextFile(fileUrl){
        var xhr = new XMLHttpRequest;
        xhr.open("GET", fileUrl); // set Method and File
        xhr.onreadystatechange = function () {
            if(xhr.readyState === XMLHttpRequest.DONE){ // if request_status == DONE
                var response = xhr.responseText;
                var instructions = response.split('\n');
                instructions.forEach(separate);
            }
        }
        xhr.send(); // begin the request
    }
    function separate(item, index, arr){
        if (item !== "")
        {
            var opcode = item.substr(0,4);
            var op1 = item.substr(4,5);
            var op2 = item.substr(9,5);
            var op3 = item.substr(14,6);
            model.append({"line":index, "opcode":opcode, "operand1":op1, "operand2":op2, "destination":op3 });
        }
    }
}
