<?php
session_start();

// 로그인 확인
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");//로그인 되어있지않으면 로그인페이지로이동
    exit;
}

// 로그아웃 처리
if (isset($_GET['logout'])) {
    session_unset();//세션삭제
    session_destroy();
    header("Location: login.php");
    exit;
}

// 데이터베이스 연결
$conn = new mysqli('localhost', 'root', 'admin#2024', 'prjTeamI');
if ($conn->connect_error) {
    die("연결 실패: " . $conn->connect_error);
}
$sql = "CREATE TABLE IF NOT EXISTS posts (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    content TEXT NOT NULL,
    ok INT NOT NULL,
    noP INT NOT NULL,
    CEN INT NOT NULL, 
    tot INT NOT NULL,
    siid VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
)";
if (!mysqli_query($conn, $sql)) {
    die('테이블 생성 실패: ' . mysqli_error($conn));
}
// 게시글 조회
$sql = "SELECT * FROM posts";
$result = $conn->query($sql);
?>
<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>홈페이지</title>
    <link rel="stylesheet" href="style.css">
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 0;
        }

        .box {
            width: 90%;
            max-width: 800px;
            margin: 20px auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 8px;
            background-color: #fff;
            overflow: hidden;
        }

        .logout-button {
            display: inline-block;
            padding: 10px 15px;
            background-color: #ff4d4d;
            color: white;
            text-decoration: none;
            border-radius: 4px;
            cursor: pointer;
        }

        .logout-button:hover {
            background-color: #ff3333;
        }

        table {
            border-collapse: collapse;
            width: 100%;
            margin-top: 20px;
        }

        th,
        td {
            border: 1px solid black;
            padding: 8px;
            text-align: left;
        }

        th {
            background-color: #f2f2f2;
            font-weight: bold;
        }

        tr:nth-child(even) {
            background-color: #f9f9f9;
        }

        tr:hover {
            background-color: #ddd;
        }

        button {
            background-color: #ff4d4d;
            color: white;
            border: none;
            padding: 5px 10px;
            cursor: pointer;
            border-radius: 4px;
        }

        button:hover {
            background-color: #ff3333;
        }
    </style>
</head>
<header class="top-bar">
    <p>로그인한 사용자: <?php echo $_SESSION['user_id']; ?></p>
    <a href="home.php?logout=true" class="logout-button" style="background-color:white; color:blue">로그아웃</a>
</header>

<body>
    <?php
    $se = $_SESSION['user_id'];
    ?>
    <!-- 게시글 목록 -->
    <div class="box">

        <h1>게시글 목록</h1>
        <table>
            <tr>
                <th>번호</th>
                <th>제목</th>


                <th colspan="2">작성자</th>

            </tr>
            <?php

            if ($result->num_rows > 0) {
                while ($row = $result->fetch_assoc()) {
                    echo "<tr style='text-align:center'>
                            <td>{$row['id']}</td>
                            <td><a href='view_post.php?id={$row['id']}'>{$row['title']}</a></td>
                            ";

                    echo "<td>{$row['siid']}</td>";
                    if ($row['siid'] == $_SESSION['user_id']) {
                        echo "<td style='text-align:center'>
                                <form action='./delete_post.php' method='POST' style='display:inline;'>
                                    <input type='hidden' name='id' value='{$row['id']}'>
                                    <button type='submit' style='width:70px;'>삭제</button>
                                </form>
                              </td>";
                    } else {
                        echo "<td style='text-align:center'>-</td>";

                    }

                }
            } else {
                echo "<tr><td colspan='5'>게시글이 없습니다.</td></tr>";
            }


            ?>
        </table>
        <form action="add_post.php" method="GET">
            <p><button style="background-color:green;">설문조사 작성</button></p>
        </form>
    </div>
</body>

</html>
<?php
$conn->close();
?>