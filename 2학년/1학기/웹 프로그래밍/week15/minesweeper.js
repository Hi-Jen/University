function mouseDown(e, element, id){
// console.log("down" + e.button +" " + leftMB + " " + rightMB);
if (e.button == 0){
    leftMB = true;
    if (rightMB== true) bothDown(element, id);
    } else if (e.button == 2){
    if (leftMB==true) bothDown(element, id);
    rightMB = true;
    }
}

function mouseUp(e, element, id){
    // console.log("up" + e.button +" " + leftMB + " " + rightMB);
    if(bothMB){
        leftMB = false;
        rightMB = false;
        bothMB = false;
    }
    if(e.button == 0){
        if(rightMB == false) leftClick(element, id);
        else{
            bothMB = true;
            bothUp(element, id);
        }
        leftMB = false;
    }
    else if (e.button == 2){
        if(leftMB == false) rightClick(element, id);
        else{
            bothMB = true;
            bothUp(element, id);
        }
        rightMB = false;
    }
}

function doNothing(e){
    //console.log("context menu clicked");
    //alert("context menu clicked");
    e.preventDefault();
}

function openCell(i,j) {
    let id = i * width + j;
    cells[id] = 2;
    bombs = bombCount(i,j);
    extBombCount = "<span class = 'count cnt" + bombs + "' >" + (bombs?bombs:"") + "</span>";
    /*
    if (bombCount==0) extBombCount = "<span class = 'count0'></span>";
    else if (bombCount==1) extBombCount = "<span class = 'count cnt1'>1</span>";
    else if (bombCount==2) extBombCount = "<span class = 'count cnt2'>2</span>";
    else if (bombCount==3) extBombCount = "<span class = 'count cnt3'>3</span>";
    else if (bombCount==4) extBombCount = "<span class = 'count cnt4'>4</span>";
    else if (bombCount==5) extBombCount = "<span class = 'count cnt5'>5</span>";
    else if (bombCount==6) extBombCount = "<span class = 'count cnt6'>6</span>";
    else if (bombCount==7) extBombCount = "<span class = 'count cnt7'>7</span>";
    else extBombCount = "<span class = count0></span>";
    */

   document.getElementById(String(id)).className = 'cellOpen';
   document.getElementById(String(id)).innerHTML = extBombCount;
   
   let won = true;
   for(let i = 0; i < height; i++){
    for (let j = 0; j < width; j++){
        id = i * width +j;
        if (cells[id] == 0){
            won = false;
            break;
            }
        }
    }
    if (won) gameOver();
}

function bombCount(i, j) {
    let bombs = 0;
    let ii;
    let jj;
    for (let k = 0; k < 8; k++){
        ii = i+neighbor[k][0];
        jj = j+neighbor[k][1];
        if(ii < 0 || height <= ii) continue;
        if(jj < 0 || width <= jj) continue;
        if (cells[ii * width + jj] == 1) bombs++;
    }
    return bombs;
}

function checkCount(i, j){
    let checks = 0;
    let ii;
    let jj;
    for (let k = 0; k < 8; k++){
        ii = i+neighbor[k][0];
        jj = j+neighbor[k][1];
        if(ii < 0 || height <= ii) continue;
        if(jj < 0 || width <= jj) continue;
        if (checked[ii * width + jj] == 1) checks++;
    }
    return checks;
}

function reset() {
    isStarted = false;
    isGameEnd = false;

    remainBombs = 99;
    curTime = 0;

    leftMB = false;
    rightMB = false;
    bothMB = false;
    savedID = 16 * 30 + 1;

    cells.fill(0);
    checked.fill(0);
    clearInterval(mylnterval);

    for(let i = 0; i < height; i++){
        for (let j = 0; j <width; j++){
            id = i * width + j;
            document.getElementById(String(id)).className = 'cellClosed';
            document.getElementById(String(id)).innerHTML = "";
            document.getElementById(String(id)).style.backgroundColor = 'lightgray';
        }
    }
}

function timeCount(){
    curTime++;
    document.getElementById('time').innerHTML = leadingZeros(curTime, 3);
    if(curTime==999){
        gameOver();
    }
}

function leadingZeros(n, digits) {
    var zero = '';
    n = n.toString();
    if(n.length < digits) {
        for (var i = 0; i < digits - n.length; i++)
            zero += '0';
    }
    return zero + n;
}

function gameOver(){
    //alert("Game Over");
    isGameEnd = true;
    clearInterval(mylnterval);
    for(let i = 0; i < height; i++){
        for(let j =0; j < width; j++){
            id = i * width + j;
            if(cells[id] == 1){
                document.getElementById(String(id)).innerHTML = "<span class = 'bomb'>◎</span>"
            } 
            if(cells[id] == 0 && checked[id] == 1){
                document.getElementById(String(id)).style.backgroundColor = 'red';
                document.getElementById(String(id)).innerHTML = "<span class = 'bomb cnt7'>●</span>"
            } 
        }
    }
}

function leftClick(element, id){
    //console.log("left mouse buttom clicked");
    //alert("left mouse buttom clicked");
    if (isGameEnd==true) return;
    if (cells[id]==1){
        document.getElementById(String(id)).style.backgroundColor = 'red';
        gameOver();
        return;
    }
    const i = parseInt(id/width);
    const j = id%width;
    let ii, jj;
    if (isStarted == false){
        for (k=0; k < nBombs; k++){
            ii = i; jj = j;
            while ((ii-i)*(ii-i)<2 && ((jj-j)**(jj-j)<2)|| cells[ii*width+jj]==1){
                ii = Math.floor((Math.random() * height));
                jj = Math.floor((Math.random() * width));
            }
            cells[ii*width+jj] = 1;
        }
        isStarted = true;
        mylnterval = setInterval(timeCount, 1000);

    }
    openCell(i,j);
}

function rightClick(element, id){
    //console.log("right mouse buttom clicked");
    //alert("right mouse buttom clicked");
    if (isGameEnd==true) return;
    if (remainBombs == 0 && checked[id] == 0) return;
    if(cells[id] == 2) return;
    const i = parseInt(id/width);
    const j = id % width;
    if (checked[id] == 1) {
        checked[id] = 0;
        remainBombs++;
        document.getElementById(String(i * width + j)).style.backgroundColor = 'lightgray';
    } else {
        checked[id] = 1;
        remainBombs--;
        document.getElementById(String(i * width + j)).style.backgroundColor = 'orange';
    }
    document.getElementById('bomb').innerHTML = leadingZeros(remainBombs, 3);
}

function bothDown(element, id){
    console.log("both mouse buttom down");
    alert("both mouse buttom down");
}

function bothUp(element, id){
    console.log("both mouse buttom up");
    alert("both mouse buttom up");
}