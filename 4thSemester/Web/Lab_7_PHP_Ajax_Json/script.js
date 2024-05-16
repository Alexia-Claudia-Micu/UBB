$(document).ready(function(){
    $("table").on('click', '.btnDelete', function () {
        let id = $(this).closest('tr').find('.carId').text();
        $.post("delete.php",{'id': id});
        $(this).closest('tr').remove();
    });

    $("table").on('click', '.btnUpdate', function () {
        let carId = $(this).closest('tr').find('.carId').text();
        let carModel = $(this).closest('tr').find('.carModel').text();
        let carEnginePower = $(this).closest('tr').find('.carEnginePower').text();
        let carFuel = $(this).closest('tr').find('.carFuel').text();
        let carPrice = $(this).closest('tr').find('.carPrice').text();
        let carColor = $(this).closest('tr').find('.carColor').text();
        let carAge = $(this).closest('tr').find('.carAge').text();
        let carHistory = $(this).closest('tr').find('.carHistory').text();
        
        $(".update_form #id").val(carId);
        $(".update_form #model").val(carModel);
        $(".update_form #enginePower").val(carEnginePower);
        $(".update_form #fuel").val(carFuel);
        $(".update_form #price").val(carPrice);
        $(".update_form #color").val(carColor);
        $(".update_form #age").val(carAge);
        $(".update_form #history").val(carHistory);
        
        if($(".update_form").css("display") === "none")
            $(".update_form").css("display", "inline");
        else
            $(".update_form").css("display", "none");
    });
});
