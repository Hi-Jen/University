<?php
session_start();
include 'db.php';

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}

$user_id = $_SESSION['user_id'];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $option_id = $_POST['option_id'];

    $check_vote = "SELECT * FROM user_votes WHERE user_id = '$user_id' AND option_id = '$option_id'";
    $vote_result = $conn->query($check_vote);

    if ($vote_result->num_rows == 0) {
        $sql = "INSERT INTO user_votes (user_id, option_id, vote_time) VALUES ('$user_id', '$option_id', NOW())";
        if ($conn->query($sql) === TRUE) {
            echo "투표 완료!";
        } else {
            echo "투표 중 오류 발생: " . $conn->error;
        }
    } else {
        echo "이미 투표하셨습니다.";
    }
}

$vote_query = "SELECT * FROM votes";
$votes = $conn->query($vote_query);
?>
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>투표</title>
    <link rel="stylesheet" href="style.css"> <!-- 스타일 적용 -->
</head>
<body>
    <div class="container">
        <h1>투표에 참여하세요</h1>
        <?php while ($vote = $votes->fetch_assoc()): ?>
            <h2><?php echo $vote['title']; ?></h2>
            <form method="POST" action="">
                <?php
                $options_query = "SELECT * FROM options WHERE vote_id = " . $vote['vote_id'];
                $options = $conn->query($options_query);
                ?>
                <?php while ($option = $options->fetch_assoc()): ?>
                    <label>
                        <input type="radio" name="option_id" value="<?php echo $option['option_id']; ?>" required>
                        <?php echo $option['option_text']; ?>
                    </label>
                <?php endwhile; ?>
                <button type="submit">투표하기</button>
            </form>
        <?php endwhile; ?>
    </div>
</body>
</html>
<?php $conn->close(); ?>
