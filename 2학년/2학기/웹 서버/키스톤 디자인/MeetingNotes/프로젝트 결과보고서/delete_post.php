<?php
$conn = new mysqli('localhost', 'root', 'admin#2024', 'prjTeamI');

if ($conn->connect_error) {
    die("연결 실패: " . $conn->connect_error);
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $id = $conn->real_escape_string($_POST['id']);
    $sql = "DELETE FROM posts WHERE id = $id";

    if ($conn->query($sql) === TRUE) {
        echo "게시글이 성공적으로 삭제되었습니다.";
    } else {
        echo "오류: " . $conn->error;
    }
}

$conn->close();
header("Location: home.php");
exit();
?>