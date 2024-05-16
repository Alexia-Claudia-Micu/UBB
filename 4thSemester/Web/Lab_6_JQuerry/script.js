$(document).ready(function() {
      function clearModalInputs() {
        $("#modalForm input[type='text']").val('');
    }
    $("#openModalBtn").click(function(event) {
      event.preventDefault(); // Prevent the default form submission
      $(this).val('');
      $("#overlay").show();
      $("#modal").show();
      clearModalInputs();
    });
  
    $("#closeModalBtn").click(function(event) {
      event.preventDefault(); // Prevent the default form submission
      $("#modalForm input").each(function() {
        var inputName = $(this).attr("name");
        var inputValue = $(this).val();
        var mainInputName = inputName.replace("modalI", "i");
        var mainInput = $("#mainForm").find(`input[name="${inputName.replace("modalI", "i")}"]`);
        var currentMainValue = mainInput.val();
        $("#mainForm").find(`input[name="${mainInputName}"]`).val(currentMainValue + inputValue);
      });
      $("#overlay").hide();
      $("#modal").hide();
    });

    $("#closeModalBtnX").click(function(event) {
      event.preventDefault(); // Prevent the default form submission
      $("#overlay").hide();
      $("#modal").hide();
  });
  
    // Prevent form submission when pressing enter in modal inputs
    $("#modalForm").submit(function(event) {
      event.preventDefault();
      $("#closeModalBtn").click(); // Trigger click on close button
    });
  });
  