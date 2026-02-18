<?php
session_start();
include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

function getNameFromUsername($usernameInp, $conn) {
    $sqlUsernameInp = "SELECT * FROM users WHERE username='$usernameInp' LIMIT 1";
    $resultUsnInp = mysqli_query($conn, $sqlUsernameInp);
    $rowFromUsnInp = mysqli_fetch_assoc($resultUsnInp);
    $middleNameOutp = !empty($rowFromUsnInp['middlename']) ? " ".$rowFromUsnInp['middlename']." " : " " ;
    return $rowFromUsnInp['firstname'].$middleNameOutp.$rowFromUsnInp['familyname'];
}

$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."' LIMIT 1";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

$sqlChats = "SELECT m1.*
FROM messages m1
INNER JOIN (
    SELECT 
        IF(username = '".$rowFromIdResult['username']."', receiver, username) AS chat_partner,
        MAX(datesent) AS max_date
    FROM messages
    WHERE isorgchat = '0' 
      AND (username = '".$rowFromIdResult['username']."' OR receiver = '".$rowFromIdResult['username']."')
    GROUP BY chat_partner
) m2 ON (
    (m1.username = '".$rowFromIdResult['username']."' AND m1.receiver = m2.chat_partner) OR 
    (m1.receiver = '".$rowFromIdResult['username']."' AND m1.username = m2.chat_partner)
) AND m1.datesent = m2.max_date
WHERE m1.isorgchat = '0'
ORDER BY m1.datesent DESC;
";

$resultChats = mysqli_query($conn, $sqlChats);
$chats = mysqli_fetch_all($resultChats, MYSQLI_ASSOC);

$output = "";

foreach ($chats as $chat) {
    //name of the person the user is talking with
    $chatParticipant = $chat['username'] === $rowFromIdResult['username'] ? $chat['receiver'] : $chat['username'];
    //name of last sender
    $chatSender = $chat['username'] === $rowFromIdResult['username'] ? "You: " : "";
    //chatId is the id of the person the user is talking with
    $sqlGetUserId = "SELECT * FROM users WHERE username='".$chatParticipant."' LIMIT 1";
    $chatId = mysqli_fetch_assoc(mysqli_query($conn, $sqlGetUserId))['id'];

    $latestMessage = $chatSender.mb_strimwidth($chat['contents'], 0, 50, "...");
    $profilePic = mysqli_fetch_assoc(mysqli_query($conn, $sqlGetUserId))['image'];

    $output = $output."<div class=\"chat-sidebar-msgr\" id=\"chat-{$chatId}\">
    <img src=\"http://".$_SERVER['HTTP_HOST']."/media/".$profilePic."\" width=60>
    <b>".getNameFromUsername($chatParticipant, $conn)."</b>
    <br />
    <span class=\"chat-sidebar-latest-msg\">{$latestMessage}</span>
    </div>";
}
echo json_encode(["contents" => $output]);
exit();