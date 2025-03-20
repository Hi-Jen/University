<?php
$conn = new mysqli('localhost', 'root', 'admin#2024', 'DB20213032');
if ($conn->connect_error) {
    die("DB 연결 실패: " . $conn->connect_error);
}

$sid = $_POST['sid'];
$q1 = $_POST['poll01'];
$q2 = $_POST['poll02'];
$q3 = $_POST['poll03'];

$q4 = [
    isset($_POST['poll10A']) ? '1' : '0',
    isset($_POST['poll10B']) ? '1' : '0',
    isset($_POST['poll10C']) ? '1' : '0',
    isset($_POST['poll10D']) ? '1' : '0',
    isset($_POST['poll10E']) ? '1' : '0',
    isset($_POST['poll10F']) ? '1' : '0',
    isset($_POST['poll10G']) ? '1' : '0'
];

$q4a = $_POST['poll10H'] ?? '';

$jpoll04 = json_encode($q4);

$sql = "UPDATE poll 
        SET q1 = '$q1', q2 = '$q2', q3 = '$q3', q4 = '$jpoll04', q4a = '$q4a'
        WHERE sid = '$sid'";
if ($conn->query($sql) === TRUE) {
    echo "데이터가 업데이트되었습니다.";
    echo "<a href='drawTableChart.php'>돌아가기</a>";
} else {
    echo "데이터 업데이트 실패: " . $conn->error;
}

$conn->close();
?>
