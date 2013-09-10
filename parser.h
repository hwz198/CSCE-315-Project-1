class parser{
 public:
  bool statement();

  bool query();
  bool rel_name();
  bool identifier();
  bool alpha();
  bool digit();
  bool expr();
  bool atomic_expr();
  bool selection();
  bool condition();
  bool conjunction();
  bool comparison();
  bool op();
  bool operand();
  bool attr_name();
  bool literal();
  bool projection();
  bool attr_list();
  bool renaming();
  bool union_rel();
  bool difference();
  bool product();

  bool command();
  bool open();
  bool close();
  bool write();
  bool exit();
  bool show();
  bool create();
  bool update();
  bool insert();
  bool delete();
  bool typed_attr_list();
  bool type();
  bool integer();
}
