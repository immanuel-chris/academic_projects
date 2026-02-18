<?php
session_start();
ob_start();

include $_SERVER['DOCUMENT_ROOT']."/db_conn.php";

if (isset($_GET['page'])) {
    $page = $_GET['page'];
}
else {
    $page = 'home';
}

if (isset($_SESSION['id'])) {
$sqlUserId = "SELECT * FROM users WHERE id='".$_SESSION['id']."' LIMIT 1";
$resultId = mysqli_query($conn, $sqlUserId);
$rowFromIdResult = mysqli_fetch_assoc($resultId);

//manage notif amounts
$sqlNotifs = "SELECT * FROM notification WHERE username='".$rowFromIdResult['username']."' AND isread=0";
$resultNotifs = mysqli_query($conn, $sqlNotifs);
$notifCount = mysqli_num_rows($resultNotifs);

//manage unread chats amounts
$sqlChats = "SELECT * FROM messages WHERE receiver='".$rowFromIdResult['username']."' AND isread=0";
$resultChats = mysqli_query($conn, $sqlChats);
$notifChats = mysqli_num_rows($resultChats);

//all unread org chats amount
$sqlOrgChats = "SELECT * FROM orgchatreadby WHERE isread=0 AND username='".$rowFromIdResult['username']."'";
$resultOrgChats = mysqli_query($conn, $sqlOrgChats);
$notifOrgChats = mysqli_num_rows($resultOrgChats);

$showChatsBool = isset($_GET['page']) ? $_GET['page'] == 'chat' : false;

$totalNotifs = $notifChats + $notifOrgChats;

function getNameFromUsername($usernameInp, $conn) {
    $sqlUsernameInp = "SELECT * FROM users WHERE username='$usernameInp' LIMIT 1";
    $resultUsnInp = mysqli_query($conn, $sqlUsernameInp);
    $rowFromUsnInp = mysqli_fetch_assoc($resultUsnInp);
    $middleNameOutp = !empty($rowFromUsnInp['middlename']) ? " ".$rowFromUsnInp['middlename']." " : " " ;
    return $rowFromUsnInp['firstname'].$middleNameOutp.$rowFromUsnInp['familyname'];
}

function getUsernameFromId($id, $conn) {
    $sqlIdInp = "SELECT * FROM users WHERE id='$id' LIMIT 1";
    $resultIdInp = mysqli_query($conn, $sqlIdInp);
    $rowFromIdInp = mysqli_fetch_assoc($resultIdInp);
    if (!empty($rowFromIdInp)) return $rowFromIdInp['username'];
    else return "";
}

function getImgFromUsername($usernameInp, $conn) {
    $sqlUsernameInp = "SELECT * FROM users WHERE username='$usernameInp' LIMIT 1";
    $resultUsnInp = mysqli_query($conn, $sqlUsernameInp);
    $rowFromUsnInp = mysqli_fetch_assoc($resultUsnInp);
    return $rowFromUsnInp['image'];
}

function getIdFromUsername($usernameInp, $conn) {
    $sqlUsernameInp = "SELECT * FROM users WHERE username='$usernameInp' LIMIT 1";
    $resultUsnInp = mysqli_query($conn, $sqlUsernameInp);
    $rowFromUsnInp = mysqli_fetch_assoc($resultUsnInp);
    return $rowFromUsnInp['id'];
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Dashboard</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
    <body>
        <div id="popupModal" class="popup">
            <div class="popup-content">
                <span id="closePopup" class="popup-close">&times;</span>
                <div class="blank-space"></div>
                <div id="popupTextContent"></div>
            </div>
        </div>
        <nav class="topbar">
            <a class="topbar-link" href=<?php echo "?page=profile&profile-id=".$_SESSION['id'] ?>><?php echo $rowFromIdResult['username']; ?></a>
            <a class="topbar-link" href="?page=contacts">Emergency Contacts</a>
            <a class="topbar-link" href="?page=about">About Us</a>
            <a class="topbar-link" href="?page=notifications">Notifications <?php echo ($notifCount > 0) ? "(".$notifCount.")" : ''; ?></a>
            <a class="topbar-link" id="chat-counter" href="?page=chat">Chats <?php echo ($totalNotifs > 0 && !$showChatsBool) ? "(".$totalNotifs.")" : ""; ?> </a>
        </nav>
        <nav class="sidebar">
            <a href="?page=home" class="<?php echo $page == 'home' ? 'active' : ''; ?>">Home</a>
            <a href="?page=tasks" class="<?php echo $page == 'tasks' ? 'active' : ''; ?>">Tasks</a>
            <a href="?page=calendar" class="<?php echo $page == 'calendar' ? 'active' : ''; ?>">Calendar</a>
            <a href="?page=settings" class="<?php echo $page == 'settings' ? 'active' : ''; ?>">Settings</a>
            <?php echo '<a href="http://'.$_SERVER['HTTP_HOST'].'/login/logout.php">Logout</a>'; ?>
        </nav>
        <main class="dashboard">
            <!-- content here should be dynamically changed based on what link in the
            navbar has been selected thru a php echo related stuff -->
            <?php 
                switch($page) {
                    case 'home':
                        include 'main.php';
                        break;
                    case 'tasks':
                        include 'tasks/tasks.php';
                        break;
                    case 'calendar':
                        include 'calendar/index.php';
                        break;
                    case 'profile':
                        include 'users/profile.php';
                        break;
                    case 'settings':
                        include 'settings/index.php';
                        break;
                    case 'notifications':
                        include 'notifications/index.php';
                        break;
                    case 'users':
                        include 'users/index.php';
                        break;
                    case 'chat':
                        include 'chat/index.php';
                        break;
                    case 'contacts':
                        include 'emergency_contact/index.php';
                        break;
                    case 'about':
                        include 'about/index.php';
                        break;
                    default:
                        include 'main.php';
                }
            ?>
        </main>
    </body>
    <script>
        //auto log out after 15 minutes
        let countdown = 900;

        function resetCountdown() {
            countdown = 900;
        }

        document.addEventListener('mousemove', resetCountdown);
        document.addEventListener('click', resetCountdown);

        setInterval(function () {
            countdown--;
            if (countdown <= 0) {
                fetch('force_logout.php')
                .then(response => response.text())
                .then(data => {
                    console.log(data); 
                    window.location.reload();
                });
            }
        }, 1000);

        //manage popup box
        var popup = document.getElementById("popupModal");
        var closeBtn = document.getElementById("closePopup");
        var content = document.getElementById("popupTextContent");

        function showPopup(val) {
            popup.style.display = "block";
            content.innerHTML = val;
        }

        closeBtn.onclick = function() {
            popup.style.display = "none";
        }

        window.onclick = function(event) {
            if (event.target == popup) {
                popup.style.display = "none";
            }
        }

        function closeButton() {
            popup.style.display = "none";
        }

        //get page name
        let params = new URLSearchParams(window.location.search);
        let pageValue = params.get('page');

        //auto clear notif amounts upon opening the notifications pages
        if (pageValue === 'notifications') {
            let notifElem = document.getElementById('notif-counter');
            notifElem.textContent = 'Notifications';
        }

        //manage notif amounts
        setInterval(function () {
            fetch('get_notif_amount.php')
            .then(response => response.json())
            .then(message => {
                let notifElem = document.getElementById('notif-counter');
                let notifCount = parseInt(message.contents);
                if (notifCount > 0) {
                    notifElem.textContent = 'Notifications ('+notifCount+')';
                }
                else {
                    notifElem.textContent = 'Notifications';
                }
            })
            .catch(error => console.error('Error:', error));
        }, 3000);

        //manage message amounts
        setInterval(function () {
            fetch('get_unread_chat_amount.php')
            .then(response => response.json())
            .then(message => {
                let chatElem = document.getElementById('chat-counter');
                let chatCount = parseInt(message.contents);
                if (chatCount > 0 && pageValue !== 'chat') {
                    chatElem.textContent = 'Chats ('+chatCount+')';
                }
                else {
                    chatElem.textContent = 'Chats';
                }
            })
            .catch(error => console.error('Error:', error));
        }, 3000);

        //show the dropdown nav
        // document.getElementById('')
    </script>
</html>
<?php 
}
else {
?>
<!DOCTYPE html>
<html>
<head>
    <title>Dashboard Unavailable</title>
    <?php echo '<link rel="stylesheet" href="http://'. $_SERVER['HTTP_HOST'] .'/style.css">' ?>
</head>
    <body class="login">
        <main class="small">
            <p class="center-block">Looks like you haven't logged in yet, or have been logged out automatically.</p>
            <?php echo '<button onclick="location.href=\'http://'. $_SERVER['HTTP_HOST'] .'/login\';">Login</button>' ?>
        </main>
    </body>
</html>
<?php
}
?>