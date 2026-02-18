This is an index of all users on Voluntech:
<div class="blank-space"></div>

<?php 
$sqlGetUsers = "SELECT * FROM users WHERE verified='1'";
$resultUsers = mysqli_query($conn, $sqlGetUsers);
$userCell = 0;

if (mysqli_num_rows($resultUsers) > 0) {
    echo "<table class=\"table-fixed-width\">";
    while ($users = mysqli_fetch_assoc($resultUsers)) {
        //opening tr tag
        if ($userCell % 4 == 0) {
            echo "<tr>";
        }

        //add name and pfp:
        $pfpHtml = "<img height='120' src='http://".$_SERVER['HTTP_HOST']."/media/".$users['image']."'>";
        $middleName = !empty($users['middlename']) ? " ".$users['middlename']." "  : " ";
        $fullName = "<a href='http://".$_SERVER['HTTP_HOST']."/dashboard/?page=profile&profile-id=".$users['id']."'>".$users['firstname'].$middleName.$users['familyname']."</a>";

        echo "<td> ".$pfpHtml."<br />".$fullName."<br />";
        if ($users['id'] != $_SESSION['id']) {
            echo "<a href='http://".$_SERVER['HTTP_HOST']."/dashboard/?page=chat&chat=".$users['id']."'>(Chat)</a>";
        }
        "</td>";
        //closing tr tag
        if ($userCell + 1 % 4 == 0) {
            echo "</tr>";
        }
        $userCell++;
    }
    echo "</table>";
}
?>