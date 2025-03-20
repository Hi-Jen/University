<?php
include 'db.php';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST['username'];
    $email = $_POST['email'];
    $password = password_hash($_POST['password'], PASSWORD_DEFAULT);

    $sql = "INSERT INTO users (username, email, password) VALUES ('$username', '$email', '$password')";
    if ($conn->query($sql) === TRUE) {
        echo "회원가입 성공!";
        header("Location: login.php");
    } else {
        echo "오류: " . $sql . "<br>" . $conn->error;
    }
}

$conn->close();
?>
<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <title>회원가입</title>
    <link rel="stylesheet" href="style.css"> <!-- 스타일 적용 -->
</head>

<body>
    <div class="container">
        <h1>회원가입</h1>
        <form method="POST" action="">
            <input type="text" name="username" placeholder="이름" required>
            <input type="email" name="email" placeholder="이메일" required>
            <input type="password" name="password" placeholder="비밀번호" required>
            <button type="submit">회원가입</button>
        </form>
    </div>
</body>

</html>