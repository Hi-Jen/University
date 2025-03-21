<?php
session_start();
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}

$conn = new mysqli('localhost', 'root', 'admin#2024', 'prjTeamI');
if ($conn->connect_error) {
    die("연결 실패: " . $conn->connect_error);
}

// 암호화 및 복호화 함수 정의
function encryptVote($vote, $key)
{
    $cipher = "aes-256-cbc";//aes 방식을 이용 대칭형 암호화 알고리즘 
    $ivlen = openssl_cipher_iv_length($cipher);//aes 방식을사용 aes는16비트이므로 초기화벡터도 16비트 길이가 같아야함
    $iv = openssl_random_pseudo_bytes($ivlen);//랜덤 iv를 생성(초기화벡터)
    $ciphertext = openssl_encrypt($vote, $cipher, $key, 0, $iv);
    //vote 데이터를 
    //cipher방식(aes)방식으로 암호화 key = 암호화키 iv를 이용해 데이터패턴을
    // 숨기고 예측불가능성 증가 결국 ciphertext는 iv + vote(암호화)의 결합상태
    return base64_encode($iv . $ciphertext);//iv가 무엇인지 명시하기위해 iv 와ciphertext를 따로 명시해서 인코딩
}

function decryptVote($encryptedVote, $key)
{
    $cipher = "aes-256-cbc";
    $data = base64_decode($encryptedVote);
    $ivlen = openssl_cipher_iv_length($cipher);
    $iv = substr($data, 0, $ivlen);
    $ciphertext = substr($data, $ivlen);
    return openssl_decrypt($ciphertext, $cipher, $key, 0, $iv);
}

$key = "your-secret-key"; // 암호화키

// VOTES 테이블이 없다면 생성
$sql = "CREATE TABLE IF NOT EXISTS VOTES (
    user_id VARCHAR(255) NOT NULL,
    post_id INT NOT NULL,
    vote TEXT NOT NULL,
    PRIMARY KEY (user_id, post_id)
)";
$conn->query($sql);

if (isset($_GET['id']) && is_numeric($_GET['id'])) {
    $post_id = $_GET['id']; // ID를 저장

    // 게시글 데이터 가져오기
    $sql = "SELECT * FROM posts WHERE id = ?";  // ? 에 실제 id값이 들어감 
    $stmt = $conn->prepare($sql);// 쿼리 준비 
    $stmt->bind_param("i", $post_id);// 사용자 입력 값 바인딩 (정수 형식) ?에 삽입
    $stmt->execute(); // 실행
    $result = $stmt->get_result();//결과가져오기

    if ($result->num_rows > 0) {
        $post = $result->fetch_assoc(); // 배열로 가져오기 $post['내용물']
    } else {
        echo "<p>존재하지 않는 게시글입니다.</p>";
        exit;
    }
} else {
    echo "<p>잘못된 접근입니다.</p>";
    exit;
}

// 설문조사 처리
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['vote'])) {
    $vote = $_POST['vote']; // 선택한 값 (ok, cen, nop)

    // 이미 투표했는지 확인
    $sql = "SELECT * FROM VOTES WHERE user_id = ? AND post_id = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("si", $_SESSION['user_id'], $post_id);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        // 이미 투표한 경우
        echo "<script>alert('이미 참여하신 설문조사입니다.'); window.location.href='home.php';</script>";
        exit;
    }

    // 투표 처리
    if (in_array($vote, ['ok', 'cen', 'nop'])) {
        $encryptedVote = encryptVote($vote, $key); // 투표 값 암호화

        // VOTES 테이블에 암호화된 투표 정보 저장
        $sql = "INSERT INTO VOTES (user_id, post_id, vote) VALUES (?, ?, ?)";// ?에 삽입
        $stmt = $conn->prepare($sql);
        $stmt->bind_param("sis", $_SESSION['user_id'], $post_id, $encryptedVote);// sis == user_id는 string문자 post_id는 int정수 encryptedVote는 string 문자형으로
        $stmt->execute();

        // 게시글의 투표 수 업데이트
        if ($vote === 'ok') {
            $sql = "UPDATE posts SET ok = ok + 1 WHERE id = ?";
        } elseif ($vote === 'cen') {
            $sql = "UPDATE posts SET cen = cen + 1 WHERE id = ?";
        } elseif ($vote === 'nop') {
            $sql = "UPDATE posts SET nop = nop + 1 WHERE id = ?";
        }
        $stmt = $conn->prepare($sql);//sql 인젝션방지
        $stmt->bind_param("i", $post_id);
        $stmt->execute();

        echo "<script>alert('투표가 완료되었습니다.'); window.location.href='home.php';</script>";
    }
}

// 모든 쿼리 실행 후 연결 종료
$conn->close();
?>

<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>게시글 보기</title>
    <link rel="stylesheet" href="style.css">
</head>
<header class="top-bar">
    <p>로그인한 사용자: <?php echo $_SESSION['user_id']; ?></p>
    <a href="home.php?logout=true" class="logout-button" style="background-color:white; color:blue">로그아웃</a>
</header>

<body>
    <div class="box">
        <h1><?php echo $post_id . "번 " . htmlspecialchars($post['title']); ?></h1>
        <div class="content">
            <p><?php echo nl2br(htmlspecialchars($post['content'])); ?></p>
        </div>

        <!-- 설문조사 -->
        <?php
        $conn = new mysqli('localhost', 'root', 'admin#2024', 'prjTeamI'); // 새 연결 생성
        $sql = "SELECT vote FROM VOTES WHERE user_id = ? AND post_id = ?";
        $stmt = $conn->prepare($sql);
        $stmt->bind_param("si", $_SESSION['user_id'], $post_id);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows > 0) {
            // 이미 투표한 경우
            $row = $result->fetch_assoc();
            $decryptedVote = decryptVote($row['vote'], $key); //복호화
            echo "<p>이미 투표하셨습니다.</p>";
        } else {
            ?>
            <div class="survey">
                <form method="post">
                    <label>
                        <input type="radio" name="vote" value="ok" required> 찬성
                    </label>
                    <label>
                        <input type="radio" name="vote" value="cen" required> 중립
                    </label>
                    <label>
                        <input type="radio" name="vote" value="nop" required> 반대
                    </label>
                    <button type="submit">제출</button>
                </form>
            </div>
            <?php
        }
        ?>
        <form method="post" action="view_result.php">
            <input type="hidden" name="post_id" value="<?php echo $post_id; ?>">
            <button type="submit">결과보기</button>
        </form>
    </div>

    <div class="box">
        <a href="home.php">목록으로 돌아가기</a>
    </div>
</body>

</html>


<style>
    body {
        font-family: Arial, sans-serif;
        margin: 0;
        padding: 0;
        background-color: #f5f5f5;
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

    h1 {
        margin-top: 0;
    }

    .content {
        max-height: 70vh;
        overflow-y: auto;
        padding: 10px;
        border: 1px solid #ddd;
        border-radius: 4px;
        background-color: #fff;
    }

    a {
        display: inline-block;
        margin-top: 20px;
        text-decoration: none;
        color: #007BFF;
    }

    a:hover {
        text-decoration: underline;
    }
</style>