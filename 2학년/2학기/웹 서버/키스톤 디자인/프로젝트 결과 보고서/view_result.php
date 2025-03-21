<?php
session_start();
$conn = new mysqli('localhost', 'root', 'admin#2024', 'prjTeamI');
if ($conn->connect_error) {
    die("연결 실패: " . $conn->connect_error);
}

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}

// POST 데이터 확인
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['post_id'])) {
    $post_id = $_POST['post_id'];

    // 게시글과 설문조사 결과 조회
    $sql = "SELECT * FROM posts WHERE id = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("i", $post_id);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        $post = $result->fetch_assoc();
    } else {
        echo "<p>존재하지 않는 게시글입니다.</p>";
        exit;
    }
} else {
    echo "<p>잘못된 접근입니다.</p>";
    exit;
}

// 설문조사 데이터 가져오기
$ok = $post['ok'];
$cen = $post['CEN'];
$nop = $post['noP'];
$tot = $ok + $nop + $cen;
if ($tot > 0) {
    $okk = ($ok / $tot) * 100;
    $nopp = ($nop / $tot) * 100;
    $cenn = ($cen / $tot) * 100;
}
;
$conn->close();

if ($tot == 0) {
    echo "<script>alert('참여인원이 없습니다.'); window.location.href='view_post.php?id=" . $post_id . "';</script>";
}
?>

<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>설문 결과</title>
    <link rel="stylesheet" href="style.css">
</head>
<header class="top-bar">
    <p>로그인한 사용자: <?php echo $_SESSION['user_id']; ?></p>
    <a href="home.php?logout=true" class="logout-button" style="background-color:white; color:blue">로그아웃</a>
</header>

<body>
    <div class="box">
        <h1><?php echo htmlspecialchars($post['title']); ?></h1>
        <p><?php echo nl2br(htmlspecialchars($post['content']));//nl2br = \n 을 <br> 로씀 ?></p>
    </div>

    <div class="box box-container">
        <div class="box2">
            <h2>설문조사 결과</h2>
            <p>참여인원:
                <?php
                if ($tot > 0) {
                    echo $tot;
                } else {
                    echo "0";
                }
                ?>명
            </p>
            <p>찬성: <?php echo $ok; ?>명</p>
            <p>중립: <?php echo $cen; ?>명</p>
            <p>반대: <?php echo $nop; ?>명</p>

            <p><?php if ($tot > 0) {
                echo "찬성 비율: " . floor($okk) . "%";
            } ?></p>
            <p><?php if ($tot > 0) {
                echo "중립 비율: " . floor($cenn) . "%";
            } ?></p>
            <p><?php if ($tot > 0) {
                echo "반대 비율: " . floor($nopp) . "%";
            } ?></p>
            <p><?php if ($tot == 0) {
                echo "투표인원이없습니다";
            } ?></p>

        </div>
        <div class="box3">
            <h2>추가 정보</h2>
            <p>설문조사 결과</p>

            <div class="bar-container">
                <p>찬성: <?php
                if ($tot > 0) {
                    echo floor($okk);
                } else {
                    echo "0";
                } ?>%</p>
                <div class="bar">
                    <div class="bar-fill" style="width: <?php echo $okk; ?>%;"></div>
                </div>
            </div>

            <div class="bar-container">
                <p>중립: <?php if ($tot > 0) {
                    echo floor($cenn);
                } else {
                    echo "0";
                } ?>%</p>
                <div class="bar">
                    <div class="bar-fill" style="width: <?php echo $cenn; ?>%;"></div>
                </div>
            </div>

            <div class="bar-container">
                <p>반대: <?php if ($tot > 0) {
                    echo floor($nopp);
                } else {
                    echo "0";
                }
                ; ?>%</p>
                <div class="bar">
                    <div class="bar-fill" style="width: <?php echo $nopp; ?>%;"></div>
                </div>
            </div>
        </div>

    </div>

    <div class="box">
        <a href="view_post.php?id=<?php echo $post_id; ?>">게시글로 돌아가기</a>
        <a href="home.php"> 목록으로 돌아가기</a>
    </div>

</body>

</html>
<?php
$sql = "INSERT INTO posts (tot) VALUE(" . $tot . ");";

?>
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

    .box2,
    .box3 {
        flex: 1;
        /* 동일한 비율로 크기 조정 */
        padding: 20px;
        border: 1px solid #ccc;
        border-radius: 8px;
        background-color: #fff;
        margin: 10px;

        text-align: center;
    }

    /* 가로 정렬 */
    .box-container {
        display: flex;
        /* Flexbox로 컨테이너 정렬 */
        justify-content: space-between;
        /* 박스 간의 여백 균일 분배 */
        align-items: flex-start;
        /* 위쪽 정렬 */
    }

    .bar-container {
        margin-bottom: 20px;
        text-align: left;
    }

    .bar {
        position: relative;
        height: 20px;
        background-color: #ddd;
        border-radius: 10px;
        overflow: hidden;
        margin-top: 5px;
        width: 100%;
    }

    .bar-fill {
        height: 100%;
        background-color: #4caf50;
        text-align: right;
        border-radius: 10px;
    }
</style>