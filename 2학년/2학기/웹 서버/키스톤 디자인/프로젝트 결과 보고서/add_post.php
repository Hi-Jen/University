<?php
session_start();
$conn = new mysqli('localhost', 'root', 'admin#2024', 'prjTeamI');
if ($conn->connect_error) {
    die("연결 실패: " . $conn->connect_error);
}

// 테이블 생성 쿼리 실행
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
    die('설문조사 테이블 생성 실패: ' . mysqli_error($conn));
}
//id 게시판번호
//title 제목
//content 내용
//ok 찬성 nop 반대 cen 중립 tot 총합 siid 작성자 

// 게시글 작성 처리
if ($_SERVER['REQUEST_METHOD'] === 'POST') {// post로 전송되었는지 확인
    $title = $conn->real_escape_string($_POST['title']); //아래의 코드에서 내용 을입력받아 $title을 저장
    $content = $conn->real_escape_string($_POST['content']);//real_Escape_String 구문으로 사용자입력에 sql명령어가 입력되었을경우를 방지 sql쿼리내에서 의도치않은 sql코드방지
    $siid = $conn->real_escape_string($_SESSION['user_id']);

    // 하나의 INSERT INTO로 작성자 ID 포함하여 저장
    $sql = "INSERT INTO posts (title, content, siid) VALUES ('$title', '$content', '$siid')"; //받은데이터를 posts 의 테이블에 저장
    if ($conn->query($sql) === TRUE) {
        echo "게시글이 성공적으로 추가되었습니다.";
        header("Location: home.php");//게시글이 성공적으로 추가되었으면 홈화면으로 이동.
        exit;
    } else {
        echo "오류: " . $conn->error;
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<header class="top-bar">
    <p>로그인한 사용자: <?php echo $_SESSION['user_id']; ?></p>
    <a href="home.php?logout=true" class="logout-button" style="background-color:white; color:blue">로그아웃</a>
</header>

<head>
    <meta charset="UTF-8">
    <title>게시글 추가</title>
    <link rel="stylesheet" href="style.css">
</head>

<body class="body">
    <div class="box">
        <p>현재 사용자: <?php echo $_SESSION['user_id']; ?></p>
        <form action="add_post.php" method="POST">
            <label for="title">제목:</label><br>
            <input type="text" maxlength="24" id="title" name="title" required placeholder="제목을 입력하세요"><br><br>

            <label for="content">내용:</label><br>
            <textarea id="conte nt" name="content" rows="5" style="width:800px;" placeholder="내용을 입력하세요"
                required></textarea><br><br>

            <button type="submit">게시글 추가</button>

        </form>

        <form action="home.php"><button>홈버튼</button></form>

    </div>
</body>

</html>

<style>
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
</style>