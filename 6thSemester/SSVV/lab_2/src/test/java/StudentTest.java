import domain.Nota;
import domain.Student;
import domain.Tema;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import repository.NotaXMLRepository;
import repository.StudentXMLRepository;
import repository.TemaXMLRepository;
import service.Service;
import validation.NotaValidator;
import validation.StudentValidator;
import validation.TemaValidator;
import validation.Validator;

import static org.junit.jupiter.api.Assertions.*;

@Tag("Student")
public class StudentTest {

    private Service service;
    private StudentXMLRepository studentXmlRepo;
    private TemaXMLRepository temaXmlRepo;

    private NotaXMLRepository notaXmlRepo;

    private Validator<Student> studentValidator;

    private Validator<Tema> temaValidator;

    private Validator<Nota> notaValidator;

    @BeforeEach
    void setUp() {

        studentValidator = new StudentValidator();
        temaValidator = new TemaValidator();
        notaValidator = new NotaValidator();

        studentXmlRepo = new StudentXMLRepository(studentValidator, "test_studenti.xml");
        temaXmlRepo = new TemaXMLRepository(temaValidator, "testTeme.xml");
        notaXmlRepo = new NotaXMLRepository(notaValidator, "testNote.xml");
        service = new Service(studentXmlRepo, temaXmlRepo, notaXmlRepo);
    }

    @Test
    void testSaveStudent_Success() {
        int result = service.saveStudent("123", "John Doe", 101);
        assertEquals(1, result, "Student should be saved successfully");
    }

    @Test
    void testSaveStudent_Failure() {
        int result;
        result = service.saveStudent("100", "John Doe", 111);
        System.out.println(result);
        result = service.saveStudent("100", "John Doe", 111);
        assertEquals(0, result, "Student should not be saved again");
        System.out.println(result);
    }
}