<?php
$conn = mysqli_connect('localhost', 'root', 'tv591100');
if (!$conn) die('Could not connect: ' . mysqli_error($conn));
if (!mysqli_select_db($conn, 'week07')) die('Can\'t use database: ' . mysqli_error($conn));

for ($i = 0; $i < 10; $i++) {
    $uid = sprintf('202400%02d', $i + 1); 
    $kor = rand(51, 100);
    $eng = rand(51, 100);
    $math = rand(51, 100); 
    $sci = rand(51, 100);
    $hist = rand(51, 100);

    $sql = "INSERT INTO data (uid, kor, eng, math, sci, hist) VALUES ('$uid', $kor, $eng, $math, $sci, $hist);";
    
    echo $sql . "<br/>";
    
    if (!mysqli_query($conn, $sql)) {
        echo 'Error inserting data: ' . mysqli_error($conn) . "\n";
    } else {
        echo 'Data is inserted' . "\n";
    }
}

mysqli_close($conn);
?>


<?php
$conn = mysqli_connect('localhost', 'root', 'tv591100'); // MySQL 서버에 'root' 사용자와 비밀번호 'tv591100'을 사용하여 연결을 시도합니다.
if (!$conn) die('Could not connect: ' . mysqli_error($conn)); // 연결이 실패하면 오류 메시지를 출력하고 스크립트를 종료합니다.
if (!mysqli_select_db($conn, 'week07')) die('Can\'t use database: ' . mysqli_error($conn)); // 'week07' 데이터베이스를 선택하고, 실패 시 오류 메시지를 출력하고 스크립트를 종료합니다.

for ($i = 0; $i < 10; $i++) { // 반복문을 통해 총 10개의 데이터를 삽입합니다.
    $uid = sprintf('202400%02d', $i + 1); // '20240001', '20240002' 형식으로 uid를 생성합니다.
    $kor = rand(51, 100); // 51에서 100 사이의 랜덤 점수를 kor 변수에 저장합니다.
    $eng = rand(51, 100); // 51에서 100 사이의 랜덤 점수를 eng 변수에 저장합니다.
    $math = rand(51, 100); // 51에서 100 사이의 랜덤 점수를 math 변수에 저장합니다.
    $sci = rand(51, 100); // 51에서 100 사이의 랜덤 점수를 sci 변수에 저장합니다.
    $hist = rand(51, 100); // 51에서 100 사이의 랜덤 점수를 hist 변수에 저장합니다.

    $sql = "INSERT INTO data (uid, kor, eng, math, sci, hist) VALUES ('$uid', $kor, $eng, $math, $sci, $hist);"; // 각 점수와 uid 값을 data 테이블에 삽입하는 SQL 쿼리 작성
    
    echo $sql . "<br/>"; // 생성된 SQL 쿼리를 화면에 출력하여 확인합니다.
    
    if (!mysqli_query($conn, $sql)) { // SQL 쿼리 실행에 실패하면 오류 메시지를 출력합니다.
        echo 'Error inserting data: ' . mysqli_error($conn) . "\n";
    } else { // SQL 쿼리가 성공적으로 실행되면 삽입 성공 메시지를 출력합니다.
        echo 'Data is inserted' . "\n";
    }
}

mysqli_close($conn); // 데이터베이스 연결을 종료합니다.
?>
