<?php
$profileId = $_SESSION['id'];
$sqlUserId = "SELECT * FROM users WHERE id='$profileId'";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);
?>

<h2>Notifications</h2>
<?php 
$username = $rowFromIdResult['username'];
$sqlNotifs = "SELECT * FROM notification WHERE username='$username' ORDER BY id DESC";
$resultNotifs = mysqli_query($conn, $sqlNotifs);
if (mysqli_num_rows($resultNotifs) > 0) {
    echo "<table class=\"task-list\">";
    while ($notif = mysqli_fetch_assoc($resultNotifs)) {
        //manage dates
        $date = new DateTime($notif['sent']);
        $dateS = "";
        $dateInterval = (new DateTime()) -> diff($date);
        if (($dateInterval->days) <= 7 && ($dateInterval->days) >= 2) {
            $dateS = ($dateInterval->days)." days ago";
        }
        else if (($dateInterval->days) == 1) {
            $dateS = "A day ago";
        }
        else if (($dateInterval->days) < 1) {
            $dateS = "Today";
        }
        else {
            $dateS = $date->format('F jS, Y');
        }

        //upon going to this page all notifications are auto-marked as read
        mysqli_query($conn, "UPDATE notification SET isread=1 WHERE id=".$notif['id']);

        //create cell
        echo "<tr>
        <td>
        <b>".$dateS."</b>
        <br />
        ".$notif['notifdesc']."
        </td>
        </tr>";
    }
    echo "</table>";
}
else {
    echo "No notifications so far...";
}
?>