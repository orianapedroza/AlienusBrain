function toAssembler(elem){
    var num = parseInt(elem,2);
    switch(num){
    case 0:
        return "STALL";
    case 1:
        return "LOAD";
    case 2:
        return "WRITE";
    case 3:
        return "ADD";
    case 4:
        return "SUB";
    case 5:
        return "DIV";
    case 6:
        return "MULT";
    case 7:
        return "LESS";
    case 8:
        return "BRANCH";
    case 9:
        return "LOADS";
    case 10:
        return "WRITES";
    case 11:
        return "NBRNCH";
    case 12:
        return "STALL";
    case 13:
        return "STALL";
    case 14:
        return "STALL";
    case 15:
        return "STALL";
    }
}
