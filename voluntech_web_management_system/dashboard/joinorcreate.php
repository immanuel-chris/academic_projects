It appears that you aren't associated yet with an organization. Please do one of the following to continue.
<br />
<table class="table-fixed-width">
    <tr>
        <th>Join An Organization</th>
        <th>Create One</th>
    </tr>
        <td>
            Join an already existing organization that has been registered here on VolunTech.
            <div class="blank-space"></div>
            <table class="table-fixed-width">
            <?php
                $orgSelect = "SELECT name FROM organizations";
                $resultOrgSelect = mysqli_query($conn, $orgSelect);
                $orgNames = [];

                while ($row = mysqli_fetch_assoc($resultOrgSelect)) {
                    $orgNames[] = $row['name'];
                }
                foreach ($orgNames as $name) {
                    if ($name !== "Staff") {
                        echo '<tr>
                            <td>'.ucwords($name).'</td>
                            <td><div class="button-container"><button>Check Out</button></div></td>
                        </tr>';
                    }
                }
            ?>
            </table>
            <table class="table-fixed-width"></table>
        </td>
        <td>
            Request for your organization to be added here.
            <form class="organization-create">
                <input type="text" name="orgname" placeholder="Organization Name"></input>
                <button type="submit">Request</button>
            </form>
        </td>
    <tr>
</tr>
</table>