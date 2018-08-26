var foreelem = '';

function mOn(){
    var elem = document.getElementById("begin");
    foreelem = elem.innerHTML;
    elem.innerHTML =
    '<h2 class="title__heading">'+        
        '<strong class="hero-section__words">'+
            'Escape Room'+
        '</strong>'+
    '</h2>'+
    '<div class="text-faded mb-5">¡Has sido encerrado junto a tu equipo! Tienen 60 minutos para descubrir las pistas que te llevarán a descubrir cómo escapar y quién está detrás de todo. </div>';
    
}

function mOut(){
    var elem = document.getElementById("begin");

    elem.innerHTML = foreelem;
    initHeadline();
    
}

