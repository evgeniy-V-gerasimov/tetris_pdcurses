#include "TetrisClassicPDC.hpp"

using namespace tetris_pdcurses;

/*
TetrisClassicPDC::VisitEvent::VisitEvent(TetrisClassicPDC* obj): instance(obj) {} 


void TetrisClassicPDC::VisitEvent::operator()( const ContEvent::BlockLanded&){
	std::set<std::size_t> affected_blocks;
	affected_blocks = instance->game_field.erase_full_lines();
	instance->game_field.split_blocks(affected_blocks);
	//std::cout << "BlockLanded" << '\n';
}
void TetrisClassicPDC::VisitEvent::operator()( const ContEvent::CtrlBlockLanded&){
	//std::cout << "CtrlBlockLanded" << '\n';
	std::set<std::size_t> affected_blocks;
	affected_blocks = instance->game_field.erase_full_lines();
	instance->game_field.split_blocks(affected_blocks);
	if(not instance->spawnBlock() ) {
		instance->exit_game = true;
	}
}
void TetrisClassicPDC::VisitEvent::operator()( const ContEvent::BlockSpawned&){
	std::cout << "BlockSpawned" << '\n';
}
void TetrisClassicPDC::VisitEvent::operator()( const ContEvent::Sanitize&){
	instance->game_field.sanitizeRemoved();
}
**/	



TetrisClassicPDC::TetrisClassicPDC()
	: game_field(20, 10)
	, pdc_window_width(40)
	, pdc_window_height(24)
	, pdc_input(-1)
	, exit_game(false)
	, index_dist(1, 9)
{ 	
	initscr();			// COLS, LINES initialized here	
	raw();
	keypad(stdscr, TRUE); //If keypad() is TRUE, and a function key is pressed, the token for that function key is returned instead of the raw characters.
	noecho();
	resize_term(25, 80); 
	mouse_set(ALL_MOUSE_EVENTS);
	PDC_save_key_modifiers(TRUE);
	PDC_return_key_modifiers(TRUE);
	//starty = (LINES - pdc_window_height) / 2;
	//startx = (COLS - pdc_window_width) / 2;
	starty = 1;
	startx = 0;
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	else {
		start_color(); // Start the color functionality
		init_pair(1, COLOR_RED, 	COLOR_BLACK);
		init_pair(2, COLOR_GREEN, 	COLOR_BLACK);
		init_pair(3, COLOR_BLUE, 	COLOR_BLACK);
		init_pair(4, COLOR_CYAN, 	COLOR_BLACK);
		init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(6, COLOR_YELLOW, 	COLOR_BLACK);
		init_pair(7, COLOR_WHITE, 	COLOR_BLACK);
		init_pair(8, COLOR_BLACK, 	COLOR_BLACK);
	}
	tetris_window = newwin(pdc_window_height, pdc_window_width, starty, startx);
	attron(COLOR_PAIR(1));
		printw("Press F1 to exit");
	attroff(COLOR_PAIR(1));
	
	wbkgd(tetris_window, A_BOLD); // brighter colors in window
	box(tetris_window, 0, 0);		//draw border on window edges
	wrefresh(tetris_window);
	refresh();
	curs_set(0);                // turn cursor off
	keypad(tetris_window, TRUE); // switch input to input window
	wtimeout(tetris_window, 0);
	wgetch(tetris_window);
}
TetrisClassicPDC::~TetrisClassicPDC() {
	 clear();
	 refresh();
}
int TetrisClassicPDC::exec() 
{
	if(not spawnBlock() ) 
		return 1; //cant spawn, exitgame
	
	rendering();
	while(not exit_game) 
	{
		pdc_input = wgetch(tetris_window);
		processInput();
		update();
		rendering();
	}
	return 0;
}
int  TetrisClassicPDC::random() 
{
	return index_dist(rng);
}
void TetrisClassicPDC::processInput()
{
	int button {0};
	if(pdc_input == ' ') { 
		game_field.drop_block();
	}
	if(pdc_input == 8){ 
		
	}
	if(pdc_input == 13){ 
		
	}
	if(pdc_input == KEY_SHIFT_R){
		rotateBlock(Rotation::Tilt_180);
	}
	if(pdc_input == KEY_ALT_R) { 
		rotateBlock(Rotation::Left_n90);
	}
	if(pdc_input == KEY_CONTROL_R) {
		rotateBlock(Rotation::Right_p90);
	}
	if(pdc_input == KEY_UP) {
		rotateBlock(Rotation::Tilt_180); 
	}
	if(pdc_input == KEY_DOWN){
		moveBlock(Direction::Down); 
	}
	if(pdc_input == KEY_LEFT){
		moveBlock(Direction::Left); 
	}
	if(pdc_input == KEY_RIGHT){
		moveBlock(Direction::Right); 
	}
	if(pdc_input == KEY_F(1)){
		exit_game = true;
	}
	if (pdc_input >= KEY_MIN){ 
	
	}
	else if (isprint(pdc_input)){ 
	
	}
	else { 
	
	}
	if (pdc_input == KEY_MOUSE) 
	{
		button = 0;
		request_mouse_pos(); 
		
		if (BUTTON_CHANGED(1)){ 
			button = 1;
		}
		else if (BUTTON_CHANGED(2)){
			button = 2;
		}
		else if (BUTTON_CHANGED(3)){
			button = 3;
		}
	if (button && (BUTTON_STATUS(button) & BUTTON_MODIFIER_MASK)) 
	{
		if (BUTTON_STATUS(button) & BUTTON_SHIFT){ 
			
		}
		if (BUTTON_STATUS(button) & BUTTON_CONTROL){ 
			
		}
		if (BUTTON_STATUS(button) & BUTTON_ALT){ 
			
		}
	}
	
	if (MOUSE_MOVED) {
		
	}
	else if (MOUSE_WHEEL_UP){ 
	
	}
	else if (MOUSE_WHEEL_DOWN){
		
	}
	else if ((BUTTON_STATUS(button) & BUTTON_ACTION_MASK) == BUTTON_PRESSED){ 
		
	}
	else if ((BUTTON_STATUS(button) & BUTTON_ACTION_MASK) == BUTTON_CLICKED){ 
	
	}
	else if ((BUTTON_STATUS(button) & BUTTON_ACTION_MASK) == BUTTON_DOUBLE_CLICKED){ 
	
	}
	else if ((BUTTON_STATUS(button) & BUTTON_ACTION_MASK) == BUTTON_TRIPLE_CLICKED){
		
	}
	else {
		
	}
	
	}
	else if ( PDC_get_key_modifiers() ){
		if (PDC_get_key_modifiers() & PDC_KEY_MODIFIER_SHIFT){ 
			
		}
		if (PDC_get_key_modifiers() & PDC_KEY_MODIFIER_CONTROL){ 
			
		}
		if (PDC_get_key_modifiers() & PDC_KEY_MODIFIER_ALT){ 
		
		}
		if (PDC_get_key_modifiers() & PDC_KEY_MODIFIER_NUMLOCK){ 
			
		}
	}
}
void TetrisClassicPDC::rendering() 
{
	draw_border();
	draw_blocks_counter();
	draw_game_field(1, 3);
}
void TetrisClassicPDC::update() 
{
	L_time_span = std::chrono::steady_clock::now() - L_time_point;
    
	if (std::chrono::duration_cast<std::chrono::seconds>(L_prev_time_span) < 
	    std::chrono::duration_cast<std::chrono::seconds>(L_time_span)) 
	{
		game_field.gravity();
		processEvents();
    }
    L_prev_time_span = L_time_span;
}
bool TetrisClassicPDC::spawnBlock()
{
	return game_field.add_block(getRandomShape() );
}
bool TetrisClassicPDC::moveBlock(const Direction dir_cmd)
{
	return game_field.move_block(dir_cmd);
}
bool TetrisClassicPDC::rotateBlock(const Rotation rot_cmd)
{
	return game_field.rotate_block(rot_cmd);
}
void TetrisClassicPDC::operator()(const Container_2D::Event::BlockLanded&)
{
	auto affected_blocks = game_field.erase_full_lines();
	if(affected_blocks.size() > 0) 
		game_field.split_blocks(affected_blocks);
}
void TetrisClassicPDC::operator()(const Container_2D::Event::CtrlBlockLanded&)
{
	auto affected_blocks = game_field.erase_full_lines();
	if(affected_blocks.size() > 0) 
		game_field.split_blocks(affected_blocks);
	if(not spawnBlock() ) {
		exit_game = true;
	}
}
void TetrisClassicPDC::operator()(const Container_2D::Event::Sanitize&)
{
	game_field.sanitizeRemoved();
}
Shape TetrisClassicPDC::getRandomShape()
{
	Shape shape {Shape::T};
	switch(random())
	{
		case 1:
			shape = Shape::Line;
			break;
		case 2: 
			shape = Shape::L;
			break;
		case 3:
			shape = Shape::rL;
			break;
		case 4:
			shape = Shape::N;
			break;
		case 5:
			shape = Shape::rN;
			break;
		case 6:
			shape = Shape::T;
			break;
		case 7:
			shape = Shape::Box;
			break;
		case 8:
			shape = Shape::Dot;
			break;
		case 9:
			shape = Shape::extBlock1;
			break;
		case 10:
			shape = Shape::extBlock2;
			break;
		case 11:
			shape = Shape::extBlock3;
			break;
		case 12:
			shape = Shape::extBlock4;
			break;
		case 13:
			shape = Shape::extBlock5;
			break;
		case 14:
			shape = Shape::extBlock6;
			break;
		case 15:
			shape = Shape::extBlock7;
			break;
		case 16:
			shape = Shape::extBlock8;
			break;
		default:
			shape = Shape::T;
	}
	return shape;
}
void TetrisClassicPDC::processEvents() 
{
	if(not game_field.hasEvents() ) return;
	
	while(game_field.hasEvents() )
	{
		std::visit(*this, game_field.getEvent() );
		game_field.popEvent();
	}
}

void TetrisClassicPDC::draw_border() const 
{
	wattron(tetris_window,COLOR_PAIR(2));
		mvwvline(tetris_window,1,1,'<', 21); // move to (1y,1x) & draw vertical line 21 symbols
		mvwvline(tetris_window,1,2,'|', 21);
		mvwvline(tetris_window,1,23,'|', 21);
		mvwvline(tetris_window,1,24,'>', 21);
		mvwhline(tetris_window,21,3,'=', 20);
		mvwhline(tetris_window,22,3,'V', 20);
	wattroff(tetris_window,COLOR_PAIR(2));
	wrefresh(tetris_window);
}
void TetrisClassicPDC::draw_blocks_counter() const 
{
	std::string counter { std::to_string(game_field.blocks_count()) };
	counter += "  "; // for clearing previous multidigit number
	wattron(tetris_window,COLOR_PAIR(2));
		mvwprintw(tetris_window,1,26, counter.c_str() );
	wattroff(tetris_window,COLOR_PAIR(2));
	wrefresh(tetris_window);
}

void TetrisClassicPDC::draw_game_field(const int y, const int x) const
{
	auto put_glyph = [wnd = tetris_window](const int color, const std::string glyph = "[]") // █ 219ASCII_ext
	{	
		wattron(wnd, COLOR_PAIR(color));
			wprintw(wnd, glyph.c_str());
		wattroff(wnd, COLOR_PAIR(color));
	};
	auto height {game_field.height()};
	for(int i{0}; i < height; ++i) {
		mvwprintw(tetris_window, y+i, x, "");
		for(auto it: game_field.row_to_str(i) ) {
			switch(it) {
				case '0':
					put_glyph(2, " .");
					break;
				case '1':
					put_glyph(2);
					break;
				case 'Y':
					put_glyph(6);
					break;
				case 'P':
					put_glyph(5);
					break;
				case 'R':
					put_glyph(1);
					break;
				case 'W':
					put_glyph(7);
					break;
				case 'B':
					put_glyph(3);
					break;
				case 'G':
					put_glyph(2);
					break;
				case 'C':
					put_glyph(4);
					break;
				default:
					put_glyph(2, "{}");
					break;
			}
		}
	}
	wrefresh(tetris_window);
}
