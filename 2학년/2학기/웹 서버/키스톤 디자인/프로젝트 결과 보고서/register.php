<?php


$login_error = "";
$conn = mysqli_connect('localhost', 'root', 'admin#2024');
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}



$sql = "CREATE DATABASE IF NOT EXISTS prjTeamI";
if (!mysqli_query($conn, $sql)) {
    die('Database creation failed: ' . mysqli_error($conn));
}
mysqli_select_db($conn, 'prjTeamI') or die('Database selection failed: ' . mysqli_error($conn));
$sql = "CREATE TABLE IF NOT EXISTS USER_info(
    sid VARCHAR(50) PRIMARY KEY, 
    spass VARCHAR(255) NOT NULL, 
    sname VARCHAR(100) NOT NULL
);";
if (!mysqli_query($conn, $sql)) {
    die('Table creation failed: ' . mysqli_error($conn));
}



if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    $id = $_POST['user_id'] ?? null;
    $pass = $_POST['user_pass'] ?? null;
    $name = $_POST['name'] ?? null;

    if (!$id || !$pass || !$name) {
        $login_error = "";
    } else {
        $sql_check = "SELECT * FROM USER_info WHERE sid = ?";
        $stmt = mysqli_prepare($conn, $sql_check);
        mysqli_stmt_bind_param($stmt, "s", $id);
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);

        if (mysqli_num_rows($result) > 0) {
            $login_error = "이미 존재하는 아이디입니다.";
        } else {
            $hashed_pass = password_hash($pass, PASSWORD_DEFAULT);

            $sql_insert = "INSERT INTO USER_info (sid, spass, sname) VALUES (?, ?, ?)";
            $stmt = mysqli_prepare($conn, $sql_insert);
            mysqli_stmt_bind_param($stmt, "sss", $id, $hashed_pass, $name);

            if (mysqli_stmt_execute($stmt)) {
                echo "<script>alert('회원가입 성공!'); window.location.href='home.php';</script>";
                exit;
            } else {
                $login_error = "회원가입 실패: " . mysqli_error($conn);
            }
        }
    }
}

mysqli_close($conn);
?>

<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="style.css">
</head>

<body class="body2">
    <div class="box">
        <h1>회원가입</h1>
        <?php if ($login_error): ?>
            <div class="error"><?php echo $login_error; ?></div>
        <?php endif; ?>
        <form action="register.php" method="post">
            <label for="user_id">아이디(학번)</label>
            <input type="text" id="user_id" name="user_id" required>
            <label for="user_pass">비밀번호</label>
            <input type="password" id="user_pass" name="user_pass" required>
            <label for="name">이름</label>
            <input type="text" id="name" name="name" required>
            <input type="submit" value="회원가입">
        </form>
        <a href="login.php">로그인</a>
    </div>
</body>

</html>