<?php
session_start();
include 'db.php';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST['email'];
    $password = $_POST['password'];

    $sql = "SELECT * FROM users WHERE email = '$email'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        if (password_verify($password, $row['password'])) {
            $_SESSION['user_id'] = $row['user_id'];
            header("Location: vote.php");
            exit;
        } else {
            echo "비밀번호가 틀렸습니다.";
        }
    } else {
        echo "이메일이 존재하지 않습니다.";
    }
}

$conn->close();
?>
<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <title>로그인</title>
    <link rel="stylesheet" href="style.css"> <!-- 스타일 적용 -->
</head>

<body>
    <div class="container">
        <h1>로그인</h1>
        <form method="POST" action="">
            <input type="email" name="email" placeholder="이메일" required>
            <input type="password" name="password" placeholder="비밀번호" required>
            <button type="submit">로그인</button>
        </form>
    </div>
</body>

</html>