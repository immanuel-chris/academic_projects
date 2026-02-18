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

function getImgFromUsername($usernameInp, $conn) {
    $sqlUsernameInp = "SELECT * FROM users WHERE username='$usernameInp' LIMIT 1";
    $resultUsnInp = mysqli_query($conn, $sqlUsernameInp);
    $rowFromUsnInp = mysqli_fetch_assoc($resultUsnInp);
    return $rowFromUsnInp['image'];
}

function getUsernameFromId($id, $conn) {
    $sqlIdInp = "SELECT * FROM users WHERE id='$id' LIMIT 1";
    $resultIdInp = mysqli_query($conn, $sqlIdInp);
    $rowFromIdInp = mysqli_fetch_assoc($resultIdInp);
    if (!empty($rowFromIdInp)) return $rowFromIdInp['username'];
    else return "";
}

//get user stuff
$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."' LIMIT 1";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

if (isset($_GET['id']) && $_GET['id'] != -1) {
    //for individual chats
    $sqlIndivChat = "SELECT * FROM messages WHERE isorgchat=0 AND ((username='".$rowFromIdResult['username']."' AND receiver='".getUsernameFromId($_GET['id'], $conn)."') OR (username='".getUsernameFromId($_GET['id'], $conn)."' AND receiver='".$rowFromIdResult['username']."')) AND id > ".$_GET['latestMsgId']." ORDER BY datesent ASC";
    $resultMessageHist = mysqli_query($conn, $sqlIndivChat);
}
else {
    $sqlGroupChat = "SELECT * FROM messages WHERE isorgchat=1 AND id > ".$_GET['latestMsgId']." ORDER BY datesent ASC";
    $resultMessageHist = mysqli_query($conn, $sqlGroupChat);
}

//get chats
$chats = array_reverse(mysqli_fetch_all($resultMessageHist, MYSQLI_ASSOC));

//get date to be put on the top and first date
$lastDate = null;
$dateToday = date("F j, Y");

//get last username
$lastUsername = "";

//print messages
$hist = "";
foreach ($chats as $chatMsg) {
    $currentDate = date('Y-m-d', strtotime($chatMsg['datesent'])); // Extract the date part
    // Check if the date has changed since the last message
    if ($lastDate !== $currentDate) {
        $displayDate = $currentDate === date('Y-m-d') ? "Today" : date('F jS, Y', strtotime($currentDate));
        //"<div class=\"chat-date-banner\">{$displayDate}</div>"
        if ($dateToday === $displayDate) {
            $hist = $hist."<div class=\"chat-date-banner\">{$displayDate}</div></br>";
        }
        $lastDate = $currentDate; // Update lastDate to the current message's date
    }

    $msgClass = ($chatMsg['username'] == $rowFromIdResult['username']) ? "chat-message-contents-logged-in" : "chat-message-contents-other";
    $msgSender = getNameFromUsername($chatMsg['username'], $conn);
    $profilePic = getImgFromUsername($chatMsg['username'], $conn);

    //set the time and date message was sent
    $dateTime = new DateTime($chatMsg['datesent']);
    $formattedDate = $dateTime->format('F jS, Y');
    $formattedTime = $dateTime->format('H:i:s');
    $sentTime = $formattedTime.", ".$formattedDate;
    
    $hist = $hist."<div id=\"blank-space-".$chatMsg['id']."\" class=\"chat-blank-space\"></div>
    <div class=\"{$msgClass}\" id='message-".$chatMsg['id']."'>
    <img src=\"http://".$_SERVER['HTTP_HOST']."/media/".$profilePic."\" width=60>
    <div class=\"chat-message-content\">
    <div class=\"chat-message-username\"><b>".$msgSender."</div></b> <br />
    <div class=\"chat-message-text\">".$chatMsg['contents']."</div>
    <span class=\"chat-message-time\">".$sentTime."</span>
    ". (($chatMsg['username'] == $rowFromIdResult['username']) ? "<span class=\"chat-message-delete-btn\" onclick=\"callDeleteMessage(".$chatMsg['id'].")\">(Delete)</span>" : "")."
    </div></div>";
    $lastUsername = $chatMsg['username'];
}
$scrollDown = $lastUsername === $rowFromIdResult['username'] ? true : false;
echo json_encode(["contents" => $hist, "scrollDown" => $scrollDown]);
exit();