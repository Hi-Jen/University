<?php
session_start();
$conn = mysqli_connect('localhost', 'root', 'admin#2024');

if (!$conn) {
    die('Connection failed: ' . mysqli_error($conn));
}

//데이터베이스 생성
$sql = "CREATE DATABASE IF NOT EXISTS prjTeamI";
if (!mysqli_query($conn, $sql)) {
    die('Database creation failed: ' . mysqli_error($conn));
}


mysqli_select_db($conn, 'prjTeamI') or die('Database selection failed: ' . mysqli_error($conn));

//유저정보 저장 테이블 생성
$sql = "CREATE TABLE IF NOT EXISTS USER_info( 
            sid VARCHAR(50) PRIMARY KEY, 
            spass VARCHAR(255) NOT NULL, 
            sname VARCHAR(100) NOT NULL
        );";
if (!mysqli_query($conn, $sql)) {
    die('Table creation failed: ' . mysqli_error($conn));
}

$login_error = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {

    $id = $_POST['user_id'];
    $password = $_POST['user_pass'];


    $sql = "SELECT * FROM USER_info WHERE sid = '$id'";
    $result = mysqli_query($conn, $sql);
    $user = mysqli_fetch_assoc($result);

    if ($user) {

        if (password_verify($password, $user['spass'])) {
            $_SESSION['user_id'] = $user['sid'];
            header('Location: home.php');
            exit;
        } else {
            $login_error = "비밀번호가 틀렸습니다.";
        }
    } else {
        $login_error = "아이디가 존재하지 않습니다.";
    }

    mysqli_close($conn);
}
?>

<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
</head>

<body class="body2">
    <div class="box">

        <h2>로그인</h2>

        <?php if ($login_error): ?>
            <div class="error"><?php echo $login_error; ?></div>
        <?php endif; ?>
        <form action="login.php" method="post" class="form-example">
            <label for="user_id">아이디(학번):</label>
            <input type="text" id="user_id" name="user_id" required></br>

            <label for="user_pass">비밀번호:</label>
            <input type="password" id="user_pass" name="user_pass" required></br>

            <input type="submit" value="로그인">
        </form>
        <form action="register.php" method="post" class="form">
            <button>회원가입</button>
        </form>
    </div>
</body>

</html>