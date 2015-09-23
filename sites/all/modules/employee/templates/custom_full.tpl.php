<strong><?php echo $text; ?></strong>
<a href="<?php echo $url; ?>"><?php echo $url; ?></a>
<table>
    <tr>
        <th>Employee id</th>
        <th>Full name</th>
        <th>Birthday</th>
        <th>User id</th>
    </tr>
    <?php
    foreach($item as $child) :
    ?>

    <tr>
        <td><?php echo $child->eid; ?></td>
        <td><?php echo $child->full_name ; ?></td>
        <td><?php echo date('Y-m-d',$child->day_of_birth) ; ?></td>
        <td><?php echo $child->uid ; ?></td>
    </tr>
<?php
endforeach ;
?>
</table>