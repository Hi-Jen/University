<?php
// db.php - 데이터베이스 연결 설정 파일
$servername = "localhost";
$username = "root";  // DB 사용자명
$password = "admin#2024";      // DB 비밀번호
$dbname = "voting_system";  // DB 이름

// MySQL 연결 생성
$conn = new mysqli($servername, $username, $password, $dbname);

// 연결 확인
if ($conn->connect_error) {
    die("연결 실패: " . $conn->connect_error);
}
?>